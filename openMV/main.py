import sensor, image, time, ustruct
from pyb import UART, LED

# todo: 光线环境校准是个问题，目前的设计是保存几个不同环境的阈值设置，或者加灯？
WHITE = (255, 255, 255)
RED = (255, 0, 0)
GREEN = (0, 255, 0)
BLUE = (0, 0, 255)
YELLOW = (255, 255, 0)

side_th=0
side_wide=20

left_roi =  (              side_th , 70, side_wide, 100)
right_roi = (320-side_th-side_wide , 70, side_wide, 100)

midle_wide=200
middle_roi = ((int)((320-midle_wide)/2), 200, midle_wide, 20)

front_roi = (0, 0, 200, 150) # todo: 注意控制在前方一格的位置
red_roi = (10, 10, 300, 180) # todo: 注意控制在前方一格的位置

#red_threshold = (36, 54, 20, 93, 2, 77)
#red_threshold =(0, 100, 127, -128, -128, 127)
grey_threshold =(0, 30, 10, -74, -52, 34)

red_area_th=2000 # todo: 设置面积
red_threshold =(0, 81, 75, 6, -4, 69)
object=0
cx=0x00

red_led   = LED(1)
green_led = LED(2)
blue_led  = LED(3)


clock = time.clock()
uart = UART(3, 115200) # todo: 几号口不确定

def IMG_init():
    sensor.reset()
    sensor.set_pixformat(sensor.RGB565)
    sensor.set_framesize(sensor.QVGA)
    sensor.skip_frames(20)
    sensor.set_auto_gain(False)
    sensor.set_auto_whitebal(False)
    red_led.on()
    green_led.on()
    blue_led.on()

def sending_data(cx,cy):
    global uart;
    data = ustruct.pack("<bbhb",             #格式为俩个字符俩个短整型(2字节)
                   0x86,                     #帧头1
                   cx,                       #数据1 路径节点标志位
                   cy,                       #数据2 巡线中心标志位
                   0x54)
    uart.write(data);

# 串口初始化
if __name__ == '__main__':
    IMG_init()
    while(True):
        # cx - 路径节点标志位，cy - 中线偏差位
        cy = 256
        cx = 0

        clock.tick() # Track elapsed milliseconds between snapshots().
        img = sensor.snapshot() # 从感光芯片获得一张图像

        # todo: 每条线最好加个面积过滤
        left_line_blobs = img.find_blobs([grey_threshold], merge = True, roi = left_roi)
        right_line_blobs = img.find_blobs([grey_threshold], merge = True, roi = right_roi)
        middle_line_blobs = img.find_blobs([grey_threshold], merge = True, roi = middle_roi)
        red_blobs = img.find_blobs([red_threshold], pixels_threshold=150, roi=red_roi, area_threshold=130)
        front_line_blobs = img.find_blobs([grey_threshold], roi = front_roi)

        if red_blobs:
            b = max(red_blobs, key=lambda x: x.area())
            img.draw_circle((b.cx(), b.cy(),int((b.w()+b.h())/4)))
            if b.pixels() > red_area_th:
                cx = cx|bx00010000   #宝藏
            else :
                cx = cx|bx00001000   #陷阱

        if left_line_blobs:
            # 左线
            cx=cx|bx00000001
            b = max(left_line_blobs, key=lambda x: x.area())
            # frame_position_storage_list[0] = b[6] + 100 # 0~300 -> 100~400
            # Draw a rect around the blob.
            img.draw_rectangle(b[0:4], color = RED, thickness = 2) # rect
            img.draw_cross(b[5], b[6], color = RED, thickness = 2) # cx, cy

        if right_line_blobs:
            # 右线
            cx=cx|bx00000100
            b = max(right_line_blobs, key=lambda x: x.area())
            # frame_position_storage_list[1] = b[6] + 100 # 0~300 -> 100~400
            # Draw a rect around the blob.
            img.draw_rectangle(b[0:4], color = GREEN, thickness = 2) # rect
            img.draw_cross(b[5], b[6], color = GREEN, thickness = 2) # cx, cy


        if middle_line_blobs:
            b = max(middle_line_blobs, key=lambda x: x.area())
            # frame_position_storage_list[2] = b[5] - 220 + 10 # 220~420 -> 10~210
            # Draw a rect around the blob.
            img.draw_rectangle(b.rect(), color = YELLOW, thickness = 2) # rect
            img.draw_cross(b[5], b[6], color = YELLOW, thickness = 2) # cx, cy
            cy=int(((b.cx()-(int)((320-midle_wide)/2))/midle_wide)*100)
            print(cy)

        # todo: ROI 待调整
        if front_line_blobs:
            # 下一段中线
            cx=cx|bx00000010
            b = max(front_line_blobs, key=lambda x: x.area())

        sending_data(cx, cy)
        #uart.write(str(frame_position_storage_list))
        #print(clock.fps(), "position: array", "L:", frame_position_storage_list[0], "R: ", frame_position_storage_list[1], "MID: ", frame_position_storage_list[2], "FRONT_LANE_EXSIST: ",  frame_position_storage_list[3]) # 注意: 你的OpenMV连到电脑后帧率大概为原来的一半
        #print("uart output: ", str(frame_position_storage_list))
        #如果断开电脑，帧率会增加

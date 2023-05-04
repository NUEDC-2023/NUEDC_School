import sensor, image, time
from pyb import UART

# todo: 光线环境校准是个问题，目前的设计是保存几个不同环境的阈值设置，或者加灯？
# todo: 保障识别暂时没写
WHITE = (255, 255, 255)
RED = (255, 0, 0)
GREEN = (0, 255, 0)
BLUE = (0, 0, 255)
YELLOW = (255, 255, 0)

# todo: ROI 待调整
left_roi = (0, 0, 100, 300)
right_roi = (560, 0, 100, 300)
middle_roi = (220, 300, 200, 50)
front_roi = (220, 0, 200, 50) # todo: 注意控制在前方一格的位置

red_threshold = (36, 54, 20, 93, 2, 77)

sensor.reset() # 初始化摄像头
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.VGA)
sensor.skip_frames(time = 2000)
sensor.set_auto_gain(False)
sensor.set_auto_whitebal(False)
clock = time.clock()

# 串口初始化
uart = UART(3, 9600) # todo: 几号口不确定

while(True):
    # 初始化后面发送到串口的四个值：左转线上下位置（100-400 / 0），右转线上下位置（100-400 / 0）， 正前方线段偏移（正数 0-200，100为中）， 最前方是否有线（1/0）：
    frame_position_storage_list = [0, 0, 0, 0]
    clock.tick() # Track elapsed milliseconds between snapshots().
    img = sensor.snapshot() # 从感光芯片获得一张图像

    left_line_blobs = img.find_blobs([red_threshold], merge = True, roi = left_roi)
    right_line_blobs = img.find_blobs([red_threshold], merge = True, roi = right_roi)
    middle_line_blobs = img.find_blobs([red_threshold], merge = True, roi = middle_roi)
    front_line_blobs = img.find_blobs([red_threshold], merge = True, roi = front_roi)

    # todo: 每条线最好加个面积过滤
    if left_line_blobs:
        b = max(left_line_blobs, key=lambda x: x.area())
        frame_position_storage_list[0] = b[6] + 100 # 0~300 -> 100~400
        # Draw a rect around the blob.
        img.draw_rectangle(b[0:4], color = RED, thickness = 2) # rect
        img.draw_cross(b[5], b[6], color = RED, thickness = 2) # cx, cy

    if right_line_blobs:
        b = max(right_line_blobs, key=lambda x: x.area())
        frame_position_storage_list[1] = b[6] + 100 # 0~300 -> 100~400
        # Draw a rect around the blob.
        img.draw_rectangle(b[0:4], color = GREEN, thickness = 2) # rect
        img.draw_cross(b[5], b[6], color = GREEN, thickness = 2) # cx, cy


    if middle_line_blobs:
        b = max(middle_line_blobs, key=lambda x: x.area())
        frame_position_storage_list[2] = b[5] - 220 # 220~420 -> 0~200
        # Draw a rect around the blob.
        img.draw_rectangle(b.rect(), color = YELLOW, thickness = 2) # rect
        img.draw_cross(b[5], b[6], color = YELLOW, thickness = 2) # cx, cy

    if front_line_blobs:
        frame_position_storage_list[3] = 1 # 0/1
        # Draw a point on the image:
        img.draw_circle(320, 20, 10, color = RED, fill = True)

    uart.write(str(frame_position_storage_list))
    #print(clock.fps(), "position: array", "L:", frame_position_storage_list[0], "R: ", frame_position_storage_list[1], "MID: ", frame_position_storage_list[2], "FRONT_LANE_EXSIST: ",  frame_position_storage_list[3]) # 注意: 你的OpenMV连到电脑后帧率大概为原来的一半
    print("uart output: ", str(frame_position_storage_list))
    #如果断开电脑，帧率会增加

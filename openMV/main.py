import sensor, image, time, ustruct
from pyb import UART, LED
WHITE = (255, 255, 255)
RED = (255, 0, 0)
GREEN = (0, 255, 0)
BLUE = (0, 0, 255)
YELLOW = (255, 255, 0)

sensor_brightnes = 1

side_th=25
side_wide=22

middle_wide=200
front_wide = 200

end_roi = (58, 50, 220, 50)
left_roi =  (			  side_th , 110, side_wide, 150)
right_roi = (320-side_th-side_wide , 110, side_wide, 150)
middle_roi = ((int)((320-middle_wide)/2), 210, middle_wide, 20)
front_roi = ((int)((320-front_wide)/2), 90, front_wide , 20)
treasure_roi = (10, 10, 300, 100) # twrk 必须在最前面，保证没有阻塞动作会执行

# Good map
grey_middle_threshold = (0, 60, -6, 9, -42, 8)
grey_right_threshold = (16, 47, -6, 9, -42, 8)
grey_left_threshold = (16, 47, -6, 9, -42, 8)
grey_front_threshold = (5, 63, -30, 15, -13, 12)
end_threshold = (10, 29, -5, 101, -128, 1)
treasure_threshold = (34, 74, -80, -39, 17, 68)

# 203? night
#grey_middle_threshold = (21, 64, -15, 18, -22, -2)
#grey_right_threshold = (25, 56, -24, 35, -40, 28)
#grey_left_threshold = (25, 62, -24, 35, -40, 28)
#grey_front_threshold = (21, 80, -10, 10, -18, -1)
#end_threshold = (25, 53, 26, 81, 23, 54)
#treasure_threshold = (34, 74, -80, -39, 17, 68)

#grey_middle_threshold = (30, 58, 9, -13, -19, 19)
#grey_right_threshold = (19, 54, -18, 22, -25, 8)
#grey_left_threshold = (19, 54, -24, 15, -24, 5)
#grey_front_threshold = (10, 75, -20, 19, -26, 4)
#end_threshold = (25, 53, 26, 81, 23, 54)
#treasure_threshold = (24, 48, 6, 60, 4, 52) # twrk

end_area_th = 9000
front_area_th = 300
side_area_th = 100
side_area_max_th = 800
treasure_area_th=400 # twrk
middle_area_th = 600
side_detect_th = 140
# middle_area_max_th = 1200

object=0
cx=0x00

red_led   = LED(1)
green_led = LED(2)
blue_led  = LED(3)

clock = time.clock()
uart = UART(3, 115200)

def IMG_init():
    sensor.reset()
    sensor.set_pixformat(sensor.RGB565)
    sensor.set_framesize(sensor.QVGA)
    sensor.set_auto_gain(False)
    sensor.set_auto_whitebal(False)
    sensor.set_auto_exposure(False, exposure_us  = 13427)
    sensor.skip_frames(100)

    red_led.on()
    green_led.on()
    blue_led.on()

def sending_data(cx,cy):
    global uart;
    data = ustruct.pack("<bbhb",
                   0x86,
                   cx,
                   cy,
                   0x54)
    uart.write(data);

if __name__ == '__main__':
    IMG_init()
    while(True):
        cy = 256
        cx = 0b00000000
        clock.tick()
        img = sensor.snapshot()

        end_blobs = img.find_blobs([end_threshold],  merge = True, roi = end_roi)
        left_line_blobs = img.find_blobs([grey_left_threshold], merge = True, roi = left_roi)
        right_line_blobs = img.find_blobs([grey_right_threshold], merge = True, roi = right_roi)
        middle_line_blobs = img.find_blobs([grey_middle_threshold], merge = True, roi = middle_roi)
        treasure_blobs = img.find_blobs([treasure_threshold], merge = True, roi=treasure_roi)
        front_line_blobs = img.find_blobs([grey_front_threshold],merge = True,  roi = front_roi)

        if treasure_blobs:
            b = max(treasure_blobs, key=lambda x: x.area())
            if b.pixels() > side_area_th :
                img.draw_circle((b.cx(), b.cy(),int((b.w()+b.h())/4)))
                cx = cx|0b00001000

        a_sentinal = False
        b_sentinal = False
        if left_line_blobs:
            a = max(left_line_blobs, key=lambda x: x.area())
            a_sentinal = True
            img.draw_rectangle(a[0:4], color = RED, thickness = 2)
            img.draw_cross(a[5], a[6], color = RED, thickness = 2)
            if a.pixels() > side_area_th and a.cy() > side_detect_th :
                cx=cx|0b00000001
            else:
                left_line_blobs = False;

        if right_line_blobs:
            b = max(right_line_blobs, key=lambda x: x.area())
            b_sentinal = True
            img.draw_rectangle(b[0:4], color = GREEN, thickness = 2)
            img.draw_cross(b[5], b[6], color = GREEN, thickness = 2)
            if b.pixels() > side_area_th and b.cy() > side_detect_th:
                cx=cx|0b00000100
            else:
                right_line_blobs = False;

        if a_sentinal and b_sentinal:
            if b.pixels() > side_area_th and a.pixels() > side_area_th:
                if a.cy() > side_detect_th or b.cy() > side_detect_th:
                    cx = cx|0b00000101

        if end_blobs:
            b = max(end_blobs, key=lambda x: x.area())
            if b.pixels() > end_area_th:
                cx = 0
                cx = cx|0b10000000
                img.draw_rectangle(b[0:4], color = WHITE, thickness = 1)
                img.draw_cross(b[5], b[6], color = WHITE, thickness = 1)

        if middle_line_blobs:
            b = max(middle_line_blobs, key=lambda x: x.area())
            if b.pixels() > middle_area_th :
                img.draw_rectangle(b.rect(), color = YELLOW, thickness = 2)
                img.draw_cross(b[5], b[6], color = YELLOW, thickness = 2)
                cy=int(((b.cx()-(int)((320-middle_wide)/2))/middle_wide)*100)
            else:
                middle_line_blobs = False;

        if front_line_blobs:
            b = max(front_line_blobs, key=lambda x: x.area())
            if  b.pixels() > front_area_th:
                cx=cx|0b00000010
                img.draw_rectangle(b.rect(), color = WHITE, thickness = 2)
                img.draw_cross(b[5], b[6], color = WHITE, thickness = 2)

        print(cx)
        sending_data(cx, cy)

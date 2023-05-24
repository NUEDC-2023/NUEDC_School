import sensor, image, time, ustruct
from pyb import UART, LED
WHITE = (255, 255, 255)
RED = (255, 0, 0)
GREEN = (0, 255, 0)
BLUE = (0, 0, 255)
YELLOW = (255, 255, 0)

sensor_brightnes = 1

side_th=20
side_wide=20

middle_wide=200
front_wide = 120

end_roi = (58, 100, 220, 50)
left_roi =  (			  side_th , 130, side_wide, 130)
right_roi = (320-side_th-side_wide , 130, side_wide, 130)
middle_roi = ((int)((320-middle_wide)/2), 220, middle_wide, 20)
front_roi = ((int)((320-front_wide)/2), 80, front_wide , 20)
red_roi = (10, 10, 300, 180)

# grey_threshold =(0, 30, 10, -74, -52, 34)
# grey_middle_threshold = (18, 45, -10, 19, -31, 0) # with mask
# grey_right_threshold = (15, 44, -20, 16, -30, 15)# with mask
# grey_left_threshold = (20, 44, -20, 16, -30, 15)# with mask

# nolight 203
# grey_middle_threshold = (10, 32, -17, 19, -31, 21)
# grey_right_threshold = (12, 37, -10, 19, -21, 20)
# grey_left_threshold = (12, 37, -30, 24, -41, 23)
# front_grey_threshold = (31, 54, -20, 19, -26, 4)

grey_middle_threshold = (30, 56, 9, -13, -19, 19)
grey_right_threshold = (19, 47, -18, 22, -25, 1)
grey_left_threshold = (30, 47, -24, 15, -40, 5)
front_grey_threshold = (31, 54, -20, 19, -26, 4)
end_threshold = (25, 53, 26, 81, 23, 54)
red_threshold = (24, 48, 6, 60, 4, 52)

end_area_th = 9000
side_area_th = 100
side_area_max_th = 800
red_area_th=2000 # 待調整
middle_area_th = 600
side_detect_th = 165
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
    sensor.set_auto_exposure(False, exposure_us  = 10000)
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
        red_blobs = img.find_blobs([red_threshold], pixels_threshold=150, roi=red_roi, area_threshold=130)
        front_line_blobs = img.find_blobs([front_grey_threshold], roi = front_roi)

        if red_blobs:
            b = max(red_blobs, key=lambda x: x.area())
            img.draw_circle((b.cx(), b.cy(),int((b.w()+b.h())/4)))
            if b.pixels() > red_area_th:
                cx = cx|0b00010000
            else :
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
            cx=cx|0b00000010
            b = max(front_line_blobs, key=lambda x: x.area())
            img.draw_rectangle(b.rect(), color = WHITE, thickness = 2)
            img.draw_cross(b[5], b[6], color = WHITE, thickness = 2)

        print(cx)
        sending_data(cx, cy)

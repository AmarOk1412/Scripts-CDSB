import time
from cv2_detect import detect
import cv2
import cv2.cv as cv
import numpy


def detectOnPict(in_fn, out_fn):
    '''draw the detection on a picture'''
    img_color = cv2.imread(in_fn)
    #get the gray level of the pict
    img_gray = cv2.cvtColor(img_color, cv.CV_RGB2GRAY)
    img_gray = cv2.equalizeHist(img_gray)
    rects = detect(img_gray)
    img_out = img_color.copy()
    #Replace face with a picture
    trollImage = cv2.imread("trollface.png")
    for x1, y1, x2, y2 in rects:
        trollImage = cv2.resize(trollImage, (x2-x1, y2-y1))
        img_out[y1:y1+trollImage.shape[0], x1:x1+trollImage.shape[1]] = trollImage
    cv2.imwrite(out_fn, img_out)


def main():
    vc = cv2.VideoCapture(0)

    if vc.isOpened(): # try to get the first frame
        rval, frame = vc.read()
    else:
        rval = False

    while rval:
        #Convert a frame into a picture
        cv.SaveImage('pic.png', cv.fromarray(frame))
        detectOnPict('pic.png', 'pic.detect.jpg')
        image = cv.LoadImage('pic.detect.jpg',cv.CV_LOAD_IMAGE_UNCHANGED)
        cv.NamedWindow('my window', cv.CV_WINDOW_AUTOSIZE)
        cv.ShowImage('my window', image) # show the frame with the detection
        rval, frame = vc.read()
        key = cv2.waitKey(20)
        if key == 27: # exit on ESC
            break


if __name__ == '__main__':
    main()

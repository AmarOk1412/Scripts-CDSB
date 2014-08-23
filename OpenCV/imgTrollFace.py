import sys
from cv2_detect import detect #LastFile
import cv2
import cv2.cv as cv


def detectOnPict(in_fn, out_fn):
    '''draw the detection on a picture'''
    img_color = cv2.imread(in_fn)
    #get the gray level of the pict
    img_gray = cv2.cvtColor(img_color, cv.CV_RGB2GRAY)
    img_gray = cv2.equalizeHist(img_gray)
    rects = detect(img_gray)#CF cv2_detect.py
    img_out = img_color.copy()
    #sys.argv[3] = image to overlay
    trollImage = cv2.imread(sys.argv[3])
    for x1, y1, x2, y2 in rects:
        #Resize at the size of the face
        trollImage = cv2.resize(trollImage, (x2-x1, y2-y1))
        #Overlay
        img_out[y1:y1+trollImage.shape[0], x1:x1+trollImage.shape[1]] = trollImage
    cv2.imwrite(out_fn, img_out)


def main():
    #sys.argv[1] : ImageIn, #sys.argv[2] : ImageOut
    detectOnPict(sys.argv[1], sys.argv[2])


if __name__ == '__main__':
    main()

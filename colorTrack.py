import cv
from Xlib import X, display
import subprocess

global imgHSV

def getContourAndDetectColour(im):
	'''Get 2 colours'''
	global imgHSV
	imgHSV = cv.CreateImage(cv.GetSize(im), 8, 3)

        # Convert image from RGB to HSV
	cv.CvtColor(im,imgHSV,cv.CV_BGR2HSV)

	# A little change here. Creates images for blue and yellow (or whatever color you like).
	imgyellow = cv.CreateImage(cv.GetSize(im), 8, 1)
	imgblue = cv.CreateImage(cv.GetSize(im), 8, 1)

	imgthreshold = cv.CreateImage(cv.GetSize(im),8,1)

	cv.InRangeS(imgHSV, cv.Scalar(20,100,100), cv.Scalar(30,255,255), imgyellow)	# Select a range of yellow color
	cv.InRangeS(imgHSV ,cv.Scalar(100,100,100), cv.Scalar(120,255,255), imgblue)	# Select a range of blue color
	cv.Add(imgyellow, imgblue, imgthreshold)

        #We can detect more colours (create a new colour and Add)
	return imgthreshold

######################################## MAIN ALGORITHM ########################################
capture=cv.CaptureFromCAM(0)
frame = cv.QueryFrame(capture)
frame_size = cv.GetSize(frame)
img2=cv.CreateImage(cv.GetSize(frame), 8, 3)

while(1):
	color_image = cv.QueryFrame(capture)
        #Because my webcam set an horizontal mirror
	cv.Flip(color_image,color_image,1)
        #TODO
	imgDetectColour = getContourAndDetectColour(color_image)
	#Group pixels (for having an easiest detection
        cv.Erode(imgDetectColour, imgDetectColour, None, 3)
        #Dilate x 10
	cv.Dilate(imgDetectColour, imgDetectColour, None, 10)

        #Get the contours into 2 levels
	contour = cv.FindContours(imgDetectColour, cv.CreateMemStorage(0), cv.CV_RETR_CCOMP, cv.CV_CHAIN_APPROX_SIMPLE)	

	while contour:
		# Draw rect on colour Image, return x1, x2, y1, y2
		bound_rect = cv.BoundingRect(list(contour))
		contour = contour.h_next()
		pt1 = (bound_rect[0], bound_rect[1])
		pt2 = (bound_rect[0] + bound_rect[2], bound_rect[1] + bound_rect[3])
		cv.Rectangle(color_image, pt1, pt2, cv.CV_RGB(2,100,87), 3)

	        #Calculate new pointer position
		pointerx = cv.Round((pt1[0]+pt2[0])/2)
		pointery = cv.Round((pt1[1]+pt2[1])/2)
                #If we see yellow, control mouse button (require xdotool), we can change with pyMouse
		if (20 < cv.Get2D(imgHSV,pointery,pointerx)[0] < 30):
                        if pointerx < frame_size[0]/2 and pointery > frame_size[1]/2:
                            subprocess.call('xdotool click 1', shell=True)
			elif pointerx > frame_size[0]/2 and pointery > frame_size[1]/2:
                            subprocess.call('xdotool click 3', shell=True)
                        elif pointerx < frame_size[0]/2 and pointery > frame_size[1]/2:
                            subprocess.call('xdotool click 4', shell=True)
                        else:
                            subprocess.call('xdotool click 4', shell=True)
                #Else, if we have blue move the mouse
		elif (100 < cv.Get2D(imgHSV,pointery,pointerx)[0] < 120):
                        d = display.Display()
                        s = d.screen()
                        root = s.root
                        root.warp_pointer(float(s.width_in_pixels)/(float(float(frame_size[0])/float(pointerx))), float(s.height_in_pixels)/(float(float(frame_size[1])/float(pointery))))
                        d.sync()


	#Show the Result
	cv.ShowImage("Seuil", img2)
	cv.ShowImage("Real", color_image)
	if cv.WaitKey(20) == 27: #Exit the app on Escape Press
		cv.DestroyWindow("Real")
		cv.DestroyWindow("Threshold")
		break

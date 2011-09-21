/*
 * How to test v4l2loopback:
 * 1. launch this test program (even in background), it will initialize the
 *    loopback device and keep it open so it won't loose the settings.
 * 2. Feed the video device with data according to the settings specified
 *    below: size, pixelformat, etc.
 *    For instance, you can try the default settings with this command:
 *    mencoder video.avi -ovc raw -nosound -vf scale=640:480,format=yuy2 -o /dev/video1
 *    TODO: a command that limits the fps would be better :)
 *
 * Test the video in your favourite viewer, for instance:
 *   luvcview -d /dev/video1 -f yuyv
 */

#include <linux/videodev2.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <assert.h>
#include <sys/ioctl.h>

#include "opencv.h"

#define VIDEO_DEVICE "/dev/video1"
#define FRAME_WIDTH  640
#define FRAME_HEIGHT 480

#define FRAME_SIZE (FRAME_WIDTH * FRAME_HEIGHT * 3)

int v4l2init()
{

    CvCapture* capt=cvCreateCameraCapture(200);
  IplImage* img= cvQueryFrame(capt);;
  IplImage* img_out;
  cvNamedWindow("Cam",0);
  img_out=cvCreateImage(cvGetSize(img),img->depth,img->nChannels);



    struct v4l2_capability vid_caps;
        struct v4l2_format vid_format;


        FILE* fdwr = fopen(VIDEO_DEVICE, "wd");
        assert(fdwr != NULL);

        int ret_code = ioctl(fileno(fdwr), VIDIOC_QUERYCAP, &vid_caps);
        assert(ret_code != -1);

        memset(&vid_format, 0, sizeof(vid_format));

        vid_format.type = V4L2_BUF_TYPE_VIDEO_OUTPUT;
        vid_format.fmt.pix.width = FRAME_WIDTH;
        vid_format.fmt.pix.height = FRAME_HEIGHT;
        vid_format.fmt.pix.pixelformat = V4L2_PIX_FMT_BGR24;
        vid_format.fmt.pix.sizeimage = FRAME_WIDTH * FRAME_HEIGHT * 3;
        vid_format.fmt.pix.field = V4L2_FIELD_NONE;
        vid_format.fmt.pix.bytesperline = FRAME_WIDTH * 3;
        vid_format.fmt.pix.colorspace = V4L2_COLORSPACE_SRGB;

        ret_code = ioctl(fileno(fdwr), VIDIOC_S_FMT, &vid_format);
        assert(ret_code != -1);

        while(1)
        {
       komiks(img,img_out);
    fseek(fdwr,0,SEEK_SET);
       fwrite(img_out->imageData, FRAME_SIZE,1,fdwr);
            cvShowImage("Cam",img_out);
       img= cvQueryFrame(capt);
        if( cvWaitKey( 100 ) == 27 )
         break;
    }
        /* check if we get the same data on output */
        /*
        int fdr = open(VIDEO_DEVICE, O_RDONLY);
        read(fdr, check_buffer, FRAME_SIZE);
        for (i = 0; i < FRAME_SIZE; ++i) {
                if (buffer[i] != check_buffer[i])
                        assert(0);
        }
        */


        fclose(fdwr);
        cvReleaseCapture(&capt);
         cvReleaseImage(&img);
        cvDestroyWindow("Cam");


        cvReleaseImage(&img_out);
        return 0;

        }


int v4l2close()
{
return 0;
}


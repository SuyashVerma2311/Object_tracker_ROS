#include<opencv2/highgui.hpp>
#include<opencv2/opencv.hpp>
#include<opencv2/tracking.hpp>

int main(int argc, char ** argv)
{
	cv::Mat frame;
	cv::VideoCapture video("video.mp4");
	if(!video.isOpened()) return -1;
	int frameWidth = video.get(cv::CAP_PROP_FRAME_WIDTH);
	int frameHeight = video.get(cv::CAP_PROP_FRAME_HEIGHT);
	cv::VideoWriter output("processed_video.avi", cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), 15, cv::Size(frameWidth, frameHeight));
	cv::Ptr<cv::Tracker> track  = cv::TrackerKCF::create();
	video.read(frame);
	cv::Rect2d trackbox = cv::selectROI(frame, false);
	track->init(frame, trackbox);
	while(video.read(frame)) {
		if(track->update(frame, trackbox)) {
			cv::rectangle(frame, trackbox, cv::Scalar(100,255,0), 2, 8);
		}
		cv::imshow("Video Out", frame);
		output.write(frame);
		if(cv::waitKey(12)>=0) break;
	}
	output.release();
	video.release();
	cv::destroyAllWindows();
	return 0;
}

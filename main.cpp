#include <iostream>
#include <chrono>
#include "mykeypoints.hpp"
#include "mytransforms.hpp"

void convert_to_filename(int level, int i, std::string* filenames)
{
	auto l = std::to_string(level);
	if ( i == 10 )
	{
		filenames[0] = "mosaic/Level" + std::to_string(level) + "/" + l + "-010-2.ppm";
		filenames[1] = "mosaic/Level" + std::to_string(level) + "/" + l + "-010-1.ppm";
        filenames[2] = "mosaic/Level" + std::to_string(level) + "/" + l + "-010.txt";
	}
	else
	{
		filenames[0] = "mosaic/Level" + std::to_string(level) + "/" + l + "-00" + std::to_string(i) + "-2.ppm";
		filenames[1] = "mosaic/Level" + std::to_string(level) + "/" + l + "-00" + std::to_string(i) + "-1.ppm";
        filenames[2] = "mosaic/Level" + std::to_string(level) + "/" + l + "-00" + std::to_string(i) + ".txt";
	}
};

#include <cstring>

int main(int argc, char *argv[])
{
	for ( int level = 1; level != 4; ++level )
	{
		for ( int i = 1; i != 11; ++i ) 
		{
			std::string filenames[3];
			convert_to_filename(level, i, filenames);
			MyKeyPoints kp(filenames[0], filenames[1]);
			
            cv::Mat_< cv::Vec3b > rgb_image1 = cv::imread(filenames[0], 1);
			cv::Mat_< cv::Vec3b > rgb_image2 = cv::imread(filenames[1], 1);
            
			const auto startTime = std::chrono::system_clock::now();
	
            // select feature
            if (argc > 1 && strstr(argv[1], "adjust"))
            {
                std::cout << "adjust\n";
                kp.adjust_init();
            }
            else
            {
                kp.init();
            }
            
            
            // select using RGBs or not
            if (argc > 1 && std::strstr(argv[1], "threshold") != NULL)
            {
                mosaic_with_helmat(rgb_image1, rgb_image2, kp.points1, kp.points2, Helmat::threshold);
            }
            else if (argc > 1 && std::strstr(argv[1], "weight") != NULL)
            {
                mosaic_with_helmat(rgb_image1, rgb_image2, kp.points1, kp.points2, Helmat::weight);
            }
            else
            {
                mosaic_with_helmat(rgb_image1, rgb_image2, kp.points1, kp.points2);
            }
            
			const auto endTime = std::chrono::system_clock::now();
			const auto timeSpan = endTime - startTime;

			std::cout << "Time:" << std::chrono::duration_cast<std::chrono::milliseconds>( timeSpan ).count() << "[ms]" << std::endl;
						
			cv::waitKey(0);
			cv::destroyAllWindows();
		}
	}
	return 0;
}

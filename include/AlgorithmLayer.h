#pragma once

#include "AlgorithmLayerConfig.h"

namespace mammoth {
	namespace layer {
		class JluSlamLayer {
		public:
			~JluSlamLayer();
			static JluSlamLayer * get_instance();
			void start_slam(const std::string& gps_folder_path, const std::string& pcd_folder_path, int start_number = 0);
		private:
			void JluSlamLayer::DoTransform(float theta1, float theta2, float trans_x, float trans_y, void* pData, size_t count);
			static JluSlamLayer * layer;
			JluSlamLayer();
		};

		class DimensionReductionCluster {
		public:
			static void start_clusting(pcl::PointCloud<PointType>::Ptr & cloud);
		private:
			static std::vector<uint32_t> cube_handles;
			static pcl::PointCloud<PointType>::Ptr birdview_picture_grid(pcl::PointCloud<PointType>::Ptr& cloud);
			static int cz_region(cv::Mat src, std::vector<std::vector<cv::Point>> &points, int filter_size, bool fill_flag, int pic_width, int pic_height);
		};

		class ImuLocalization {
		public:
			ImuLocalization(float v0 = 0, float delta_t = 0.0101626);
			void calculate_distance(
				float * s,
				float * v,
				float * delta_v);
		private:
			float v0;
			float delta_t;
		};

		class ObjectDetection {
		
		};

		class ObjectTracing {

		};

		class ObjectRecognition {

		};

		class DecisionMaking {

		};

		class Planning {

		};
	}
}
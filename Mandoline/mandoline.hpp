#pragma once

#include <pcl-1.11/pcl/io/pcd_io.h>
#include <pcl-1.11/pcl/point_types.h>

#include <numeric>

namespace Mandoline
{
    class Extrude
    {
        pcl::PointCloud<pcl::PointXYZ>::Ptr m_point_cloud;
        float m_distance;

    public:
        void setInputCloud(pcl::PointCloud<pcl::PointXYZ>::Ptr const &point_cloud);

        void setDistance(float const &distance);

        void compute(pcl::PointCloud<pcl::PointXYZ> &output);

    private:
        pcl::PointXYZ extrude(std::array<pcl::PointXYZ, 3> const &points) ;
    };

    class Slice
    {
        pcl::PointCloud<pcl::PointXYZ>::Ptr m_point_cloud;
        float m_spacing;

    public:
        void setInputCloud(pcl::PointCloud<pcl::PointXYZ>::Ptr const &point_cloud);

        void setSpacing(float const &spacing);

        void compute(pcl::PointCloud<pcl::PointXYZ> &output);

    private:
        uint32_t intersections(Eigen::Vector2f const &point, std::vector<Eigen::Vector2f> const &points) const;

        bool isPointInPolygon(Eigen::Vector2f const &point, std::vector<Eigen::Vector2f> const &points) const;

        bool isPointOnSegment(Eigen::Vector2f const &point, std::array<Eigen::Vector2f, 2> const &segment, float const epsilon = 1e-4) const;
    };
}
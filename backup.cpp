#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/laser_scan.hpp>
#include <geometry_msgs/msg/twist.hpp>


// 再给我添加一个类CWallFollower, CRobot has 这个类 CWallFollower，
// 并且 CWallFollower 还实现了 P 控制，利用雷达信息
// 首先 CWallFollower 通过雷达找到最近的墙，然后当离墙一定距离后开始沿着墙走
// 如果是沿着左边走，那么就是获取雷达正前方，以及左侧各一个的雷达数据，通过这个来调节沿墙距离
// 如果是沿着右边走,反之亦然

// CLidar 类：负责管理雷达传感器的订阅和数据处理
class CLidar
{
public:
    // 构造函数：初始化雷达订阅器
    CLidar(rclcpp::Node::SharedPtr node)
        : node_(node)
    {
        // 创建一个订阅者，用于订阅/scan主题，处理雷达数据
        lidar_subscription_ = node_->create_subscription<sensor_msgs::msg::LaserScan>(
            "/scan", 10, std::bind(&CLidar::lidar_callback, this, std::placeholders::_1));
    }

    // 获取雷达数据的最近测量值
    float get_closest_distance() const
    {
        return closest_distance_;
    }

private:
    // 回调函数：处理雷达数据
    void lidar_callback(const sensor_msgs::msg::LaserScan::SharedPtr msg)
    {
        // 找到雷达数据中最小的距离（最近的障碍物）
        closest_distance_ = *std::min_element(msg->ranges.begin(), msg->ranges.end());
        RCLCPP_INFO(node_->get_logger(), "Closest obstacle at: %f meters", closest_distance_);
    }

    rclcpp::Node::SharedPtr node_;
    rclcpp::Subscription<sensor_msgs::msg::LaserScan>::SharedPtr lidar_subscription_;
    float closest_distance_ = std::numeric_limits<float>::infinity();
};

// CDriveModule 类：负责管理小车的驱动控制
class CDriveModule
{
public:
    // 构造函数：初始化驱动模块
    CDriveModule(rclcpp::Node::SharedPtr node)
        : node_(node)
    {
        // 创建一个发布者，用于发布/cmd_vel主题，控制小车的移动
        cmd_vel_publisher_ = node_->create_publisher<geometry_msgs::msg::Twist>("/cmd_vel", 10);
    }

    // 控制小车前进
    void move_forward(float speed)
    {
        auto message = geometry_msgs::msg::Twist();
        message.linear.x = speed;
        cmd_vel_publisher_->publish(message);
        RCLCPP_INFO(node_->get_logger(), "Moving forward at speed: %f", speed);
    }

    // 停止小车
    void stop()
    {
        auto message = geometry_msgs::msg::Twist();
        message.linear.x = 0.0;
        cmd_vel_publisher_->publish(message);
        RCLCPP_INFO(node_->get_logger(), "Stopping the robot");
    }

private:
    rclcpp::Node::SharedPtr node_;
    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr cmd_vel_publisher_;
};

// CRobot 类：组合了 CLidar 和 CDriveModule，并实现整体逻辑
class CRobot
{
public:
    // Only run once
    // 构造函数：初始化CRobot并创建必要的组件
    CRobot(rclcpp::Node::SharedPtr node)
        : lidar_(node), drive_module_(node), node_(node)
    {
        std::cout << "CRobot CTor STart." << std::endl;
        // 设置一个定时器，用于周期性地检查雷达数据并控制小车移动
        timer_ = node_->create_wall_timer(
            std::chrono::milliseconds(100), std::bind(&CRobot::control_loop, this));
    }

private:
    // 控制逻辑循环：根据雷达数据决定小车的行为
    void control_loop()
    {
        float distance = lidar_.get_closest_distance();

        if (distance < 0.1) {
            drive_module_.stop();  // 如果前方障碍物距离小于1米，停止小车
        } else {
            drive_module_.move_forward(0.2);  // 否则以0.2米/秒的速度前进
        }
    }

    CLidar lidar_;
    CDriveModule drive_module_;
    rclcpp::Node::SharedPtr node_;
    rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char *argv[])
{
    // 能否在代码执行前先加一个 ros2 launch turtlebot3_gazebo turtlebot3_world.launch.py
    // 然后再运行代码，并且我希望可以在代码里面制定要加载的地图

    rclcpp::init(argc, argv);  // 初始化ROS 2客户端库

    // 创建一个ROS 2节点
    auto node = rclcpp::Node::make_shared("robot_node");

    // 创建一个CRobot对象，负责控制整个机器人
    CRobot robot(node);

    // 保持节点运行，并处理回调函数
    rclcpp::spin(node);

    rclcpp::shutdown();  // 停止ROS 2客户端库

    return 0;  // 返回0表示程序成功执行
}

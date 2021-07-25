#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include <ostream>

namespace asst {

	const static std::string Version = "release.beta.03";

	enum class HandleType
	{
		Window = 1,
		View = 2,
		Control = 4
	};

	static std::ostream& operator<<(std::ostream& os, const HandleType& type)
	{
		static std::unordered_map<HandleType, std::string> _type_name = {
			{HandleType::Window, "Window"},
			{HandleType::View, "View"},
			{HandleType::Control, "Control"}
		};
		return os << _type_name.at(type);
	}

	enum class TaskType {
		Invalid = 0,
		BasicClick = 1,
		DoNothing = 2,
		Stop = 4,
		PrintWindow,
		ClickSelf = 8 | BasicClick,
		ClickRect = 16 | BasicClick,
		ClickRand = 32 | BasicClick
	};
	static bool operator&(const TaskType& lhs, const TaskType& rhs) 
	{
		return static_cast<std::underlying_type<TaskType>::type>(lhs) & static_cast<std::underlying_type<TaskType>::type>(rhs);
	}
	static std::ostream& operator<<(std::ostream& os, const TaskType& task)
	{
		static std::unordered_map<TaskType, std::string> _type_name = {
			{TaskType::Invalid, "Invalid"},
			{TaskType::BasicClick, "BasicClick"},
			{TaskType::ClickSelf, "ClickSelf"},
			{TaskType::ClickRect, "ClickRect"},
			{TaskType::ClickRand, "ClickRand"},
			{TaskType::DoNothing, "DoNothing"},
			{TaskType::Stop, "Stop"},
			{TaskType::PrintWindow, "PrintWindow"}
		};
		return os << _type_name.at(task);
	}
	
	enum class AlgorithmType {
		JustReturn,
		MatchTemplate,
		CompareHist
	};
	static std::ostream& operator<<(std::ostream& os, const AlgorithmType& type)
	{
		static std::unordered_map<AlgorithmType, std::string> _type_name = {
			{AlgorithmType::JustReturn, "JustReturn"},
			{AlgorithmType::MatchTemplate, "MatchTemplate"},
			{AlgorithmType::CompareHist, "CompareHist"}
		};
		return os << _type_name.at(type);
	}

	struct Point
	{
		Point() = default;
		Point(int x, int y) : x(x), y(y) {}
		int x = 0;
		int y = 0;
	};

	struct Rect
	{
		Rect() = default;
		Rect(int x, int y, int width, int height)
			: x(x), y(y), width(width), height(height) {}
		Rect operator*(double rhs) const
		{
			return { x, y, static_cast<int>(width * rhs), static_cast<int>(height * rhs) };
		}
		Rect center_zoom(double scale) const
		{
			int half_width_scale = static_cast<int>(width * (1 - scale) / 2);
			int half_hight_scale = static_cast<int>(height * (1 - scale) / 2);
			return { x + half_width_scale, y + half_hight_scale, width - half_width_scale,  height - half_hight_scale };
		}
		int x = 0;
		int y = 0;
		int width = 0;
		int height = 0;
	};

	struct HandleInfo {
		std::string class_name;
		std::string window_name;
	};

	struct AdbCmd {
		std::string path;
		std::string connect;
		std::string click;
		std::string display;
		std::string display_regex;
		int display_width = 0;
		int display_height = 0;
	};

	struct EmulatorInfo {
		std::string name;
		std::vector<HandleInfo> window;
		std::vector<HandleInfo> view;
		std::vector<HandleInfo> control;
		bool is_adb = false;
		AdbCmd adb;
		int width = 0;
		int height = 0;
		int x_offset = 0;
		int y_offset = 0;
		int right_offset = 0;
		int bottom_offset = 0;
	};

	struct TaskInfo {
		std::string filename;							// ͼƬ�ļ���
		double threshold = 0;							// ģ��ƥ����ֵ
		double cache_threshold = 0;						// ֱ��ͼ�Ƚ���ֵ
		TaskType type = TaskType::Invalid;				// ��������
		std::vector<std::string> next;					// ��һ�����ܵ������б���
		int exec_times = 0;								// ������ִ���˶��ٴ�
		int max_times = INT_MAX;						// �������ִ�ж��ٴ�
		std::vector<std::string> exceeded_next;			// �ﵽ��������֮����һ�����ܵ������б���
		std::vector<std::string> reduce_other_times;	// ִ���˸��������Ҫ���ٱ�������ִ�д���������ִ���˳�����ҩ����˵����һ�ε����ɫ��ʼ�ж���ťû��Ч��������ɫ��ʼ�ж�Ҫ-1
		asst::Rect specific_area;						// ָ������Ŀǰ�����ClickRect�������ã�����������
		int pre_delay = 0;								// ִ�и�����ǰ����ʱ
		int rear_delay = 0;								// ִ�и���������ʱ
	};

	struct Options {
		bool identify_cache = false;	// ͼ��ʶ�𻺴湦�ܣ���������Դ������CPU���ģ�����Ҫ��֤Ҫʶ��İ�ťÿ�ε�λ�ò���ı�
		int identify_delay = 0;			// ͼ��ʶ����ʱ��Խ�����Խ�죬��������CPU����
		int control_delay_lower = 0;	// ��������ʱ���ޣ�ÿ�ε����������������ʱ
		int control_delay_upper = 0;	// ��������ʱ���ޣ�ÿ�ε����������������ʱ
		bool print_window = false;		// ��ͼ���ܣ�������ÿ�ν��������ͼ��screenshotĿ¼��
		int print_window_delay = 0;		// ��ͼ��ʱ��ÿ�ε�������棬������Ʒ����һ���Գ����ģ��и�������������Ҫ��һ���ٽ�ͼ
	};
}
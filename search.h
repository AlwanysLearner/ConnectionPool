#include <string>
#include<vector>
#include <unordered_map>
#include <algorithm>
#include<math.h>
#include"ConnectionPool.h"
#include <string>
#include "D:/git ku/ThreadPool/ThreadPool.h"
#define M_PI 3.14159265358979323846
using namespace std;
struct Point
{
	int x;
	int y;
	string type = "";
	Point(int x, int y) {
		this->x = x;
		this->y = y;
	}
	Point(int x, int y, string type) {
		this->x = x;
		this->y = y;
		this->type = type;
	}
	bool operator<(const Point& other) const {
		return mymap[type] < mymap[other.type]; // 按照类型多少进行排序
	}
	static unordered_map<string, int> mymap ;
};

struct Line
{
public:
	Line(int first_x, int first_y, int end_x, int end_y) {
		this->first_x = first_x;
		this->first_y = first_y;
		this->end_x = end_x;
		this->end_y = end_y;
	}
	int first_x;
	int first_y;
	int end_x;
	int end_y;
};
struct polygon
{
public:
	polygon(vector<Point> points) {
		this->points = points;
	}
	vector<Point> points;
};
struct Rel
{
public:
	Rel(int angle, double dist, string type) {
		this->angle = angle;
		this->dist = dist;
		this->type = type;
	}
	Rel(int angle, int dist) {
		this->angle = angle;
		this->dist = dist;
	}
	int angle;
	double dist;
	string type = "";
};
struct DpRel
{
public:
	DpRel(int maxangle, int minangle, double maxdist, double mindist) {
		this->maxangle = maxangle;
		this->maxdist = maxdist;
		this->minangle = minangle;
		this->mindist = mindist;
	}
	int maxangle;
	int minangle;
	double maxdist;
	double mindist;
};
struct result {
	vector<Point> point;
	int dsum;
	result(vector<Point> point, int dsum) {
		this->dsum = dsum;
		this->point = point;
	}
	bool operator<(const result& other) const {
		return dsum < other.dsum; // 按照类型多少进行排序
	}
};
class search {
public:
	mutex mtx;
	vector<vector<Point>> point_condiate;
	search(vector<Point> points, vector<Line> lines, vector<polygon> polygons) {
		searchFirst(points, lines, polygons);
	};
	search(vector<Point> points) {
		baseline(points);
	}
	void baseline(vector<Point> points);
	void searchRemain(int id, vector<Rel>* ddrel, vector<Rel>* dlrel, vector<DpRel>* dprel);
	void searchFirst(vector<Point> points, vector<Line> lines, vector<polygon> polygons);
	void enumate(int a,vector<Point> temp, vector<Rel> ddrel);
	const char* sqldd1 = "select second,dist from ddrel1 where first=%d and type=%d and angle in (%d,%d,%d) order by dist limit 3";
	const char* sqldd2 = "select second from ddrel1 where first=%d and type=%d and angle in (%d,%d,%d) and dist between %d and %d";
	const char* sqldl = "select ol from bdlrel_db where od=%d and angle in (%d,%d,%d) and dist between %d and %d";
	const char* sqldp = "select op from bdprel_db where od=%d and maxangle in (%d,%d,%d) and minangle in (%d,%d,%d) and maxdist between %d and %d and mindist between %d and %d ";
	ConnectionPool* pool = ConnectionPool::getConnectPool();
	vector<vector<vector<int>>> Result;
	vector<result> result1;
	int angleswitch(double angle) {
		if (angle == 0) {
			return 0;
		}
		return ceil(angle / (M_PI / 36) - 1);
	}
	vector<Rel> pointsRel(vector<Point> points) {
		vector<Rel> ddrel;
		for (int i = 1; i < points.size(); ++i) {
			string type = points[i].type;
			double dist = sqrt((points[0].x - points[i].x) * (points[0].x - points[i].x) + (points[0].y - points[i].y) * (points[0].y - points[i].y));
			int angle = 0;
			double dy = points[i].y - points[0].y;
			double dx = points[i].x - points[0].x;
			if (points[0].x <= points[i].x && points[0].y < points[i].y) {
				angle = angleswitch(atan(dx / dy));
			}
			if (points[0].y > points[i].y) {
				angle = angleswitch(atan(dx / dy) + M_PI);
			}
			if (points[0].x > points[i].x && points[0].y < points[i].y) {
				angle = angleswitch(atan(dx / dy) + 2 * M_PI);
			}
			if (points[0].y == points[i].y && points[0].x < points[i].x) {
				angle = angleswitch(M_PI / 2);
			}
			if (points[0].y == points[i].y && points[0].x > points[i].x) {
				angle = angleswitch(3 * M_PI / 2);
			}
			ddrel.push_back(Rel(angle, dist, type));
		}
		/*for (int i = 0; i < ddrel.size(); ++i) {
			cout << ddrel[i].angle << "\\" << ddrel[i].dist << "\\" << ddrel[i].type << endl;
		}
		cout << endl;*/
		// 查找具有最大 dist 值的元素
		auto max_dist_it = std::max_element(ddrel.begin(), ddrel.end(),
			[](const Rel& rel1, const Rel& rel2) { return rel1.dist < rel2.dist; });
		//将具有最大 dist 值的元素移动到向量的开头
		if (max_dist_it != ddrel.end()) {
			std::rotate(ddrel.begin(), max_dist_it, max_dist_it + 1);
		}
		/*for (int i = 0; i < ddrel.size(); ++i) {
			cout << ddrel[i].angle << "\\" << ddrel[i].dist << "\\" << ddrel[i].type << endl;
		}*/
		return ddrel;
	}
	vector<Rel> pointLineRel(Point point, vector<Line> lines, double d) {
		vector<Rel> dlrel;
		for (int i = 0; i < lines.size(); ++i) {
			double A = lines[i].first_y - lines[i].end_y;
			double B = lines[i].end_x - lines[i].first_x;
			double C = lines[i].first_x * lines[i].end_y - lines[i].end_x * lines[i].first_y;
			int angle = 0;
			double dist = fabs((A * point.x + B * point.y + C) / sqrt(A * A + B * B)) / d;
			if (B == 0) {
				if (point.x > lines[i].first_x) {
					angle = 54;
				}
				if (point.x < lines[i].first_x) {
					angle = 18;
				}
			}
			else {
				int angle1 = atan(-A / B);
				double y = (-A / B) * point.x - C / B;
				if (y > point.y) {
					angle = angle1 > 0 ? angleswitch((2 * M_PI - angle1)) : angleswitch(angle1);
				}
				if (y < point.y) {
					angle = angleswitch(M_PI - angle1);
				}
				if (y == point.y) {
					angle = angleswitch(M_PI / 2 - angle1);
				}
			}
			dlrel.push_back(Rel(angle, dist));
		}
		return dlrel;
	}
	vector<DpRel> pointPolygonRel(Point point, vector<polygon> polygons, double d) {
		vector<DpRel> dprel;
		for (int i = 0; i < polygons.size(); ++i) {
			int minangle = 0;
			int maxangle = 71;
			double maxdist = 0;
			double mindist = LONG_MAX;
			for (int j = 0; j < polygons.at(i).points.size(); ++j) {
				double dist = sqrt((point.x - polygons.at(i).points[j].x) * (point.x - polygons.at(i).points[j].x) + (point.y - polygons.at(i).points[j].y) * (point.y - polygons.at(i).points[j].y)) / d;
				int angle = 0;
				if (point.x <= polygons.at(i).points[j].x && point.y < polygons.at(i).points[j].y) {
					angle = angleswitch(atan((polygons.at(i).points[j].x - point.x) / (polygons.at(i).points[j].y - point.y)));
				}
				if (point.y > polygons.at(i).points[j].y) {
					angle = angleswitch(atan((polygons.at(i).points[j].x - point.x) / (polygons.at(i).points[j].y - point.y)) + M_PI);
				}
				if (point.x > polygons.at(i).points[j].x && point.y < polygons.at(i).points[j].y) {
					angle = angleswitch(atan((polygons.at(i).points[j].x - point.x) / (polygons.at(i).points[j].y - point.y)) + 2 * M_PI);
				}
				if (point.y == polygons.at(i).points[j].y && point.x < polygons.at(i).points[j].x) {
					angle = angleswitch(M_PI / 2);
				}
				if (point.y == polygons.at(i).points[j].y && point.x > polygons.at(i).points[j].x) {
					angle = angleswitch(3 * M_PI / 2);
				}
				maxdist = max(dist, maxdist);
				mindist = min(dist, mindist);
				maxangle = max(angle, maxangle);
				minangle = min(angle, minangle);
			}
			dprel.push_back(DpRel(maxangle, minangle, maxdist, mindist));
		}
		return dprel;
	}
	static string UTF8ToGBK(const char* strUTF8)
	{
		int len = MultiByteToWideChar(CP_UTF8, 0, strUTF8, -1, NULL, 0);
		wchar_t* wszGBK = new wchar_t[len + 1];
		memset(wszGBK, 0, len * 2 + 2);
		MultiByteToWideChar(CP_UTF8, 0, strUTF8, -1, wszGBK, len);
		len = WideCharToMultiByte(CP_ACP, 0, wszGBK, -1, NULL, 0, NULL, NULL);
		char* szGBK = new char[len + 1];
		memset(szGBK, 0, len + 1);
		WideCharToMultiByte(CP_ACP, 0, wszGBK, -1, szGBK, len, NULL, NULL);
		std::string strTemp(szGBK);

		if (wszGBK) delete[] wszGBK;
		if (szGBK) delete[] szGBK;

		return strTemp;
	}
};





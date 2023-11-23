#include "search.h"
//unordered_map<string, int> Point::mymap = { {"事件活动", 1}, {"摩托车服务" , 2}, {"汽车销售" , 3}, {"汽车维修" , 4 }, {"风景名胜" , 5}, {"汽车服务" , 6},  {"住宿服务" , 7}, {"金融保险服务" , 8},{"公共设施" , 9},{"体育休闲服务" ,11}, {"医疗保健服务" , 10}, {"商务住宅" , 12}, {"政府机构及社会团体" , 13}, {"科教文化服务" , 15}, {"公司企业" , 16}, {"交通设施服务" , 14}, {"通行设施" , 18},{"餐饮服务" , 17},{"生活服务" , 19},{"地名地址信息" , 21},{"购物服务" , 20} };
unordered_map<string, int> Point::mymap = { {"事件活动", 1}, {"摩托车服务" , 2}, {"汽车维修" , 3}, {"汽车销售" , 4 }, {"风景名胜" , 5}, {"汽车服务" , 6}, {"公共设施" , 7}, {"住宿服务" , 8}, {"金融保险服务" , 9},{"体育休闲服务" ,10}, {"医疗保健服务" , 11}, {"商务住宅" , 12}, {"政府机构及社会团体" , 13}, {"科教文化服务" , 14}, {"公司企业" , 15}, {"交通设施服务" , 16}, {"通行设施" , 17},{"餐饮服务" , 18},{"生活服务" , 19},{"地名地址信息" , 20},{"购物服务" , 21} };
//unordered_map<string, int> Point::mymap = {  {"摩托车服务" , 1}, {"汽车销售" , 2}, {"汽车维修" , 3 }, {"风景名胜" , 4}, {"汽车服务" ,5},  {"住宿服务" , 6}, {"金融保险服务" , 7},{"公共设施" , 8},{"体育休闲服务" ,10}, {"医疗保健服务" , 9}, {"商务住宅" , 11}, {"政府机构及社会团体" , 12}, {"科教文化服务" , 14}, {"公司企业" ,15}, {"交通设施服务" , 13}, {"通行设施" , 16},{"餐饮服务" , 17},{"生活服务" , 18},{"地名地址信息" , 20},{"购物服务" , 19} };
//newyork
//unordered_map<string, int> Point::mymap= {
//		{"Aquarium", 1}, {"Castle", 2}, {"Sports", 3}, {"Living", 4}, {"Laboratory", 5},
//		{"Residence", 6}, {"Trails", 7}, {"Daycare", 8}, {"Booth", 9}, {"Distillery", 10},
//		{"Spring", 11}, {"Agency", 12}, {"Places", 13}, {"Recreation", 14}, {"Fair", 15},
//		{"Factory", 16}, {"Vineyard", 17}, {"Share", 18}, {"Union", 19}, {"Casino", 20},
//		{"Resort", 21}, {"Campground", 22}, {"Target", 23}, {"Yogurt", 24}, {"Arena", 25},
//		{"Attraction", 26}, {"Lighthouse", 27}, {"Tennis", 28}, {"Chalet", 29}, {"Planetarium", 30},
//		{"Base", 31}, {"River", 32}, {"Lodge", 33}, {"Home", 34}, {"Deck", 35}, {"Island", 36},
//		{"Racetrack", 37}, {"Shelter", 38}, {"Facility", 39}, {"Pier", 40}, {"Farm", 41},
//		{"Food", 42}, {"Non-Profit", 43}, {"Art", 44}, {"Breakfast", 45}, {"Hostel", 46},
//		{"Trail", 47}, {"Temple", 48}, {"Dealership", 49}, {"Tram", 50}, {"Cafe", 51},
//		{"Newsstand", 52}, {"Wash", 53}, {"Area", 54}, {"Site", 55}, {"Zoo", 56},
//		{"College", 57}, {"Winery", 58}, {"Quad", 59}, {"Brewery", 60}, {"Rink", 61},
//		{"Mosque", 62}, {"Lake", 63}, {"Landmark", 64}, {"Auditorium", 65}, {"Butcher", 66},
//		{"Lab", 67}, {"Dojo", 68}, {"Motel", 69}, {"Platform", 70}, {"Cemetery", 71},
//		{"Nightlife", 72}, {"Airport", 73}, {"Veterinarian", 74}, {"Multiplex", 75}, {"Consulate", 76},
//		{"Track", 77}, {"Course", 78}, {"Development", 79}, {"Arcade", 80}, {"Stadium", 81},
//		{"Pool", 82}, {"Location", 83}, {"Taxi", 84}, {"Gastropub", 85}, {"Speakeasy", 86},
//		{"Synagogue", 87}, {"City", 88}, {"Cafeteria", 89}, {"Alley", 90}, {"Plane", 91},
//		{"Rail", 92}, {"Beach", 93}, {"Classroom", 94}, {"Terminal", 95}, {"Marina", 96},
//		{"Bridge", 97}, {"Courthouse", 98}, {"Mall", 99}, {"Parlor", 100}, {"Train", 101},
//		{"House", 102}, {"Parking", 103}, {"Lookout", 104}, {"Salon", 105}, {"Court", 106},
//		{"Run", 107}, {"Market", 108}, {"Ferry", 109}, {"Travel", 110}, {"Room", 111},
//		{"Startup", 112}, {"Field", 113}, {"Museum", 114}, {"Neighborhood", 115}, {"Garden", 116},
//		{"Nightclub", 117}, {"Spot", 118}, {"Steakhouse", 119}, {"Hospital", 120}, {"Plaza", 121},
//		{"Bookstore", 122}, {"Club", 123}, {"Venue", 124}, {"Hall", 125}, {"Entertainment", 126},
//		{"Truck", 127}, {"Boutique", 128}, {"University", 129}, {"Library", 130}, {"Outdoors", 131},
//		{"Studio", 132}, {"Gate", 133}, {"Road", 134}, {"Pub", 135}, {"Playground", 136},
//		{"Lounge", 137}, {"Massage", 138}, {"Condo)", 139}, {"Service", 140}, {"Theater", 141},
//		{"Gallery", 142}, {"Garage", 143}, {"Space", 144}, {"Center", 145}, {"Station", 146},
//		{"Diner", 147}, {"Subway", 148}, {"Bakery", 149}, {"Church", 150}, {"School", 151},
//		{"Gym", 152}, {"Line", 153}, {"Hotel", 154}, {"Park", 155}, {"Joint", 156},
//		{"Barbershop", 157}, {"Pharmacy", 158}, {"Bank", 159}, {"Bodega", 160}, {"Building", 161},
//		{"Place", 162}, {"Bar", 163}, {"Office", 164}, {"Store", 165}, {"Shop", 166},
//		{"Restaurant", 167}
//};
//london
//unordered_map<string, int> Point::mymap = {
//		{"Non-Profit", 1}, {"Lighthouse", 2}, {"Newsstand", 3}, {"Arena", 4}, {"Tram", 5},
//		{"Cafe", 6}, {"Residence", 7}, {"Deck", 8}, {"Aquarium", 9}, {"Target", 10},
//		{"Shelter", 11}, {"Factory", 12}, {"Quad", 13}, {"Distillery", 14}, {"Resort", 15},
//		{"Agency", 16}, {"Fair", 17}, {"Castle", 18}, {"Planetarium", 19}, {"Yogurt", 20},
//		{"Area", 21}, {"Campground", 22}, {"Art", 23}, {"Development", 24}, {"Dojo", 25},
//		{"Stables", 26}, {"Tennis", 27}, {"Spring", 28}, {"Sports", 29}, {"Trail", 30},
//		{"Salon", 31}, {"Beach", 32}, {"Synagogue", 33}, {"Zoo", 34}, {"Ground", 35},
//		{"Rink", 36}, {"Airport", 37}, {"City", 38}, {"Auditorium", 39}, {"Facility", 40},
//		{"River", 41}, {"Base", 42}, {"Run", 43}, {"Parlor", 44}, {"Sport", 45},
//		{"Taxi", 46}, {"Motel", 47}, {"Truck", 48}, {"Racetrack", 49}, {"Location", 50},
//		{"Track", 51}, {"Classroom", 52}, {"Winery", 53}, {"Lab", 54}, {"Farm", 55},
//		{"Temple", 56}, {"Breakfast", 57}, {"Dealership", 58}, {"Speakeasy", 59}, {"Terminal", 60},
//		{"Cafeteria", 61}, {"Mosque", 62}, {"Service", 63}, {"Share", 64}, {"Brewery", 65},
//		{"Butcher", 66}, {"College", 67}, {"Parking", 68}, {"Arcade", 69}, {"Pier", 70},
//		{"Casino", 71}, {"Lake", 72}, {"Alley", 73}, {"Nightlife", 74}, {"Cemetery", 75},
//		{"Multiplex", 76}, {"Field", 77}, {"Playground", 78}, {"Site", 79}, {"Court", 80},
//		{"Courthouse", 81}, {"Ferry", 82}, {"Marina", 83}, {"Plane", 84}, {"Course", 85},
//		{"Startup", 86}, {"Consulate", 87}, {"Pool", 88}, {"Lookout", 89}, {"Bridge", 90},
//		{"Travel", 91}, {"Massage", 92}, {"Diner", 93}, {"Condo)", 94}, {"Stadium", 95},
//		{"Train", 96}, {"Hostel", 97}, {"Rail", 98}, {"House", 99}, {"Club", 100},
//		{"Steakhouse", 101}, {"Boutique", 102}, {"Garage", 103}, {"Landmark", 104}, {"Studio", 105},
//		{"Mall", 106}, {"Room", 107}, {"Bodega", 108}, {"Entertainment", 109}, {"Pharmacy", 110},
//		{"Market", 111}, {"Spot", 112}, {"Neighborhood", 113}, {"Gate", 114}, {"Venue", 115},
//		{"Hospital", 116}, {"School", 117}, {"Bookstore", 118}, {"Museum", 119}, {"Library", 120},
//		{"Lounge", 121}, {"Plaza", 122}, {"Hall", 123}, {"Garden", 124}, {"Outdoors", 125},
//		{"Barbershop", 126}, {"Gallery", 127}, {"Bank", 128}, {"Nightclub", 129}, {"Church", 130},
//		{"Platform", 131}, {"University", 132}, {"Bakery", 133}, {"Gastropub", 134}, {"Subway", 135},
//		{"Joint", 136}, {"Road", 137}, {"Space", 138}, {"Line", 139}, {"Theater", 140},
//		{"Gym", 141}, {"Center", 142}, {"Park", 143}, {"Building", 144}, {"Station", 145},
//		{"Place", 146}, {"Hotel", 147}, {"Bar", 148}, {"Office", 149}, {"Shop", 150},
//		{"Store", 151}, {"Pub", 152}, {"Restaurant", 153}
//};
//tokyo
//unordered_map<string, int> Point::mymap = {
//		{"Mountain", 1}, {"Laboratory", 2}, {"Well", 3}, {"Castle", 4}, {"Synagogue", 5},
//		{"Non-Profit", 6}, {"Trails", 7}, {"City", 8}, {"Target", 9}, {"Supply", 10},
//		{"Lighthouse", 11}, {"Shelter", 12}, {"Terminal", 13}, {"Speakeasy", 14}, {"Deck", 15},
//		{"Farm", 16}, {"Plane", 17}, {"Rink", 18}, {"Mosque", 19}, {"Newsstand", 20},
//		{"Sport", 21}, {"Share", 22}, {"Facility", 23}, {"Base", 24}, {"Aquarium", 25},
//		{"Airport", 26}, {"Taxi", 27}, {"Quad", 28}, {"Racetrack", 29}, {"Wash", 30},
//		{"Track", 31}, {"Salon", 32}, {"Dojo", 33}, {"Art", 34}, {"Courthouse", 35},
//		{"Planetarium", 36}, {"Zoo", 37}, {"Campground", 38}, {"Sports", 39}, {"Factory", 40},
//		{"Resort", 41}, {"River", 42}, {"Home", 43}, {"Beach", 44}, {"Food", 45},
//		{"Motel", 46}, {"Breakfast", 47}, {"Agency", 48}, {"Pier", 49}, {"Classroom", 50},
//		{"Winery", 51}, {"Spot", 52}, {"Veterinarian", 53}, {"Marina", 54}, {"Auditorium", 55},
//		{"Service", 56}, {"Startup", 57}, {"Run", 58}, {"Location", 59}, {"Lake", 60},
//		{"Condo)", 61}, {"College", 62}, {"Multiplex", 63}, {"Lab", 64}, {"Area", 65},
//		{"Casino", 66}, {"Neighborhood", 67}, {"Truck", 68}, {"Dealership", 69}, {"Lookout", 70},
//		{"Attraction", 71}, {"Brewery", 72}, {"Hostel", 73}, {"Cemetery", 74}, {"Alley", 75},
//		{"Spring", 76}, {"Cafeteria", 77}, {"Ferry", 78}, {"Stadium", 79}, {"Gastropub", 80},
//		{"Lounge", 81}, {"Church", 82}, {"Market", 83}, {"Course", 84}, {"Butcher", 85},
//		{"Travel", 86}, {"Pool", 87}, {"Studio", 88}, {"Train", 89}, {"Plaza", 90},
//		{"Court", 91}, {"Consulate", 92}, {"Cafe", 93}, {"Parking", 94}, {"Rail", 95},
//		{"Trail", 96}, {"Platform", 97}, {"Landmark", 98}, {"Nightlife", 99}, {"Site", 100},
//		{"Line", 101}, {"Entertainment", 102}, {"Nightclub", 103}, {"Garage", 104}, {"Field", 105},
//		{"Boutique", 106}, {"Garden", 107}, {"Arcade", 108}, {"Outdoors", 109}, {"Museum", 110},
//		{"Room", 111}, {"Gym", 112}, {"Gallery", 113}, {"Theater", 114}, {"Club", 115},
//		{"Library", 116}, {"Bodega", 117}, {"Venue", 118}, {"Hall", 119}, {"Playground", 120},
//		{"Massage", 121}, {"Temple", 122}, {"Space", 123}, {"University", 124}, {"Pub", 125},
//		{"Mall", 126}, {"Hospital", 127}, {"Barbershop", 128}, {"Shrine", 129}, {"Steakhouse", 130},
//		{"Place", 131}, {"Center", 132}, {"Subway", 133}, {"School", 134}, {"Bakery", 135},
//		{"Pharmacy", 136}, {"Bank", 137}, {"Hotel", 138}, {"Diner", 139}, {"Bridge", 140},
//		{"Bookstore", 141}, {"Park", 142}, {"Building", 143}, {"Road", 144}, {"Joint", 145},
//		{"Station", 146}, {"Office", 147}, {"House", 148}, {"Bar", 149}, {"Shop", 150},
//		{"Store", 151}, {"Restaurant", 152}
//};
bool cmp(vector<vector<int>> R1, vector<vector<int>> R2) {
	return R1[0][2] < R2[0][2];
}

	

void search::searchRemain(int id, vector<Rel>* ddrel, vector<Rel>* dlrel, vector<DpRel>* dprel)
{
	shared_ptr<MysqlConn> conn = pool->getConnection();
	char sql[1024] = { 0 };
	sprintf(sql, sqldd1, id, Point::mymap[ddrel->at(0).type], ddrel->at(0).angle, (ddrel->at(0).angle + 1) % 72, (ddrel->at(0).angle + 71) % 72);
	//cout << sql << endl;
	conn->query(sql);
	while (conn->next()) {
		int dsum = stoi(conn->value(1));
		vector<vector<int>> result;
		vector<int> d1;
		d1.push_back(id);
		d1.push_back(stoi(conn->value(0)));
		result.push_back(d1);
		bool break_out = false;
		shared_ptr<MysqlConn> conn1 = pool->getConnection();
		for (int i = 1; i < ddrel->size(); ++i) {
			int d = ddrel->at(i).dist * stoi(conn->value(1));
			//cout << ddrel->at(i).dist <<"\\" << stoi(conn->value(1)) <<"\\" << d << endl;;
			sprintf(sql, sqldd2, id, Point::mymap[ddrel->at(i).type], ddrel->at(i).angle, (ddrel->at(i).angle + 1) % 72, (ddrel->at(i).angle + 71) % 72, d - 2, d + 2);
			//cout << sql << endl;
			/*if (id == 5210) {
				cin.get();
			}*/
			conn1->query(sql);
			vector<int> td;
			while (conn1->next()) {
				td.push_back(stoi(conn1->value(0)));
			}
			if (td.size() == 0) {
				break_out = true;
				break;
			}
			dsum += d;
			result.push_back(td);
		}
		if (break_out) {
			continue;
		}
		for (int i = 0; i < dlrel->size(); ++i) {
			int d = dlrel->at(i).dist * stoi(conn->value(1));
			sprintf(sql, sqldl, id, dlrel->at(i).angle, (dlrel->at(i).angle + 1) % 72, (dlrel->at(i).angle + 71) % 72, d - 5, d + 5);
			//cout << sql << endl;
			conn1->query(sql);
			vector<int> tl;
			while (conn1->next()) {
				tl.push_back(stoi(conn1->value(0)));
			}
			if (tl.size() == 0) {
				break_out = true;
				break;
			}
			dsum += d;
			result.push_back(tl);
		}
		if (break_out) {
			continue;
		}
		for (int i = 0; i < dprel->size(); ++i) {
			int maxd = dprel->at(i).maxdist * stoi(conn->value(1));
			int mind = dprel->at(i).mindist * stoi(conn->value(1));
			//cout << maxd <<" "<< mind << endl;
			sprintf(sql, sqldp, id, dprel->at(i).maxangle, (dprel->at(i).maxangle + 1) % 72, (dprel->at(i).maxangle + 71) % 72, dprel->at(i).minangle, (dprel->at(i).minangle + 1) % 72, (dprel->at(i).minangle + 71) % 72, maxd - 5, maxd + 5, mind - 5, mind + 5);
			//cout << sql << endl;
			conn1->query(sql);
			vector<int> tp;
			while (conn1->next()) {
				tp.push_back(stoi(conn1->value(0)));
			}
			if (tp.size() == 0) {
				break_out = true;
				break;
			}
			dsum += mind;
			result.push_back(tp);
		}
		if (break_out) {
			continue;
		}
		//cout <<"成功：" << id << endl;
		result[0].push_back(dsum);
		lock_guard<std::mutex> guard(mtx);
		Result.push_back(result);
		//cout <<"记录：" << id << endl;
	}
}

void search::searchFirst(vector<Point> points, vector<Line> lines, vector<polygon> polygons)
{
	//处理数据
	//排序点要素按类型多少
	sort(points.begin(), points.end());
	vector<Rel> ddrel1 = pointsRel(points);
	vector<Rel>* ddrel = &ddrel1;
	vector<DpRel> dprel1 = pointPolygonRel(points[0], polygons, ddrel->at(0).dist);
	vector<DpRel>* dprel = &dprel1;
	vector<Rel> dlrel1 = pointLineRel(points[0], lines, ddrel->at(0).dist);
	vector<Rel>* dlrel =&dlrel1;
	double xdist = ddrel->at(0).dist;
	for (int i = 0; i < ddrel->size(); ++i) {
		ddrel->at(i).dist /= xdist;
	}
	/*for (int i = 0; i < ddrel->size(); ++i) {
		cout << ddrel->at(i).angle << "\\" << ddrel->at(i).dist << "\\" << ddrel->at(i).type << endl;
	}*/
	//cin.get();
	shared_ptr<MysqlConn> conn = pool->getConnection();
	/*char sql[1024] = { 0 };
	sprintf(sql, "select id from obj_tb where type_1='%s'", UTF8ToGBK(points[0].type.c_str()));*/
	string sql = "select id from obj_tb where type_1='" + points[0].type + "'";
	//cout << sql << endl;
	conn->query(sql);
	vector<int> firstID;
	while (conn->next()) {
		firstID.push_back(stoi(conn->value(0)));
	}
	/*ThreadPool tpool(64);
	vector< std::future<int> > res;*/
	for (int i = 0; i < firstID.size(); ++i) {
		searchRemain(firstID[i], ddrel, dlrel, dprel);
		/*res.emplace_back(tpool.enqueue([this,i](int id, vector<Rel>* ddrel, vector<Rel>* dlrel, vector<DpRel>* dprel) { searchRemain(id, ddrel, dlrel, dprel); return i; }, firstID[i], ddrel, dlrel, dprel));*/
	}
	//std::this_thread::sleep_for(std::chrono::seconds(1));
	//结果集排序并打印输出
	//for (auto&& result : res)
		//result.get();
	//cout << Result.size()<<endl;
	sort(Result.begin(), Result.end(), cmp);
	/*cout << Result.size() << endl;*/
	/*cout << "结果集:" << endl;
	for (auto i = Result.begin(); i != Result.end(); ++i) {
		for (auto j = i->begin(); j != i->end(); ++j) {
			for (auto k = j->begin(); k != j->end(); ++k) {
				cout << *k << " ";
				
			}
			cout <<"\\" ;
		}
		cout << endl<<endl;
	}*/
}

void search::baseline(vector<Point> points)
{
	vector<Rel> ddrel=pointsRel(points);
	MysqlConn conn;
	conn.connect("root", "Ssy2000226..", "test_db", "localhost");
	for (int i = 0; i < points.size();++i) {
		string sql = "select xz,yz from obj_tb where type_1='" + points[i].type + "'";
		conn.query(sql);
		vector<Point> firstID;
		while (conn.next()) {
			firstID.push_back(Point(stoi(conn.value(0)), stoi(conn.value(1))));
		}
		point_condiate.push_back(firstID);
	}
	vector<Point> temp;
	enumate(0,temp,ddrel);
	sort(result1.begin(), result1.end());
	cout << result1.size() << endl;
}
void search::enumate(int a, vector<Point> temp, vector<Rel> ddrel)
{
	cout << 1;
	for (int i = 0; i < point_condiate[a].size(); ++i) {
		temp.push_back(point_condiate[a][i]);
		if (a < point_condiate.size()-1) {
			enumate(a+1, temp,ddrel);
		}
		else {
			//判断
			vector<Rel> ddrel1 = pointsRel(temp);
			if (ddrel1[0].angle == ddrel[0].angle)
			{
				int j = 1;
				int dsum = ddrel1[0].dist;
				for (; j < ddrel1.size(); ++j) {
					if (ddrel1[j].angle != ddrel[j].angle || ddrel1[j].dist/ddrel[j].dist!= ddrel1[0].dist / ddrel[0].dist) {
						break;
					}
					dsum += ddrel1[j].dist;
				}
				if (j == ddrel1.size()) {
					result1.push_back(result(temp,dsum));
				}
			}
		}
		temp.pop_back();//回溯
	}
}

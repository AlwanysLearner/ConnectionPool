#include <iostream>
#include<thread>
#include"MysqlConn.h"
#include"ConnectionPool.h"
#include<unordered_map>
#include<vector>
#include<string>
#include <fstream>
#include <sstream>
#include"search.h"
using namespace std;
void op1(int begin ,int end) {
    for (int i = begin; i <= end; ++i) {
        MysqlConn conn;
        conn.connect("root", "Ssy2000226..", "test_db", "localhost");
        char sql[1024] = { 0 };
        sprintf(sql, "insert into person values(%d,'tom',25,'man')", i);
        conn.update(sql);
    }
}

void op2(ConnectionPool* pool, int begin, int end) {
    for (int i = begin; i <= end; ++i) {
        shared_ptr<MysqlConn> conn = pool->getConnection();
        char sql[1024] = { 0 };
        sprintf(sql, "insert into person values(%d,'java',25,'男')", i);
        cout << sql << endl;
        conn->update(sql);
    }
}
void test1() {
#if 0
    steady_clock::time_point begin = steady_clock::now();
    op1(1, 5000);
    steady_clock::time_point end = steady_clock::now();
    auto length = end - begin;
    cout << "非连接池，单线程:" << length.count() / 1000000 << "毫秒" << endl;
#else
    ConnectionPool* pool = ConnectionPool::getConnectPool();
    steady_clock::time_point begin = steady_clock::now();
    op2(pool,1, 5000);
    steady_clock::time_point end = steady_clock::now();
    auto length = end - begin;
    cout << "连接池，单线程:" << length.count() / 1000000 << "毫秒" << endl;
#endif
}
void test2() {
#if 1
    MysqlConn conn;
    conn.connect("root", "Ssy2000226..", "test_db", "localhost");
    steady_clock::time_point begin = steady_clock::now();
    thread t1(op1, 1, 1000);
    thread t2(op1, 1001, 2000);
    thread t3(op1, 2001, 3000);
    thread t4(op1, 3001, 4000);
    thread t5(op1, 4001, 5000);
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
    steady_clock::time_point end = steady_clock::now();
    auto length = end - begin;
    cout << "非连接池，多线程:" << length.count() / 1000000 << "毫秒" << endl;
#else
    ConnectionPool* pool = ConnectionPool::getConnectPool();
    steady_clock::time_point begin = steady_clock::now();
    thread t1(op2,pool, 1, 1000);
    thread t2(op2,pool, 1001, 2000);
    thread t3(op2,pool, 2001, 3000);
    thread t4(op2,pool, 3001, 4000);
    thread t5(op2,pool, 4001, 5000);
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
    steady_clock::time_point end = steady_clock::now();
    auto length = end - begin;
    cout<< "连接池，多线程:" << length.count() / 1000000 << "毫秒" << endl;
#endif
}
int query(){
    MysqlConn conn;
    conn.connect("root", "Ssy2000226..", "test_db", "localhost");
    string sql = "insert into person values(6,'tom',25,'man')";
    bool flag=conn.update(sql);
    cout << "falg value:" << flag << endl;
    sql = "select * from person";
    conn.query(sql);
    while (conn.next()) {
        cout << conn.value(0) << ","
            << conn.value(1) << ","
            << conn.value(2) << ","
            << conn.value(3) <<endl;
    }
    return 0;
}
void WriteMyMapToFile(const std::unordered_map<std::string, std::vector<int>>& my_map, const std::string& file_path) {
    std::ofstream ofs(file_path, std::ios::binary);
    if (!ofs) {
        throw std::runtime_error("Error opening file " + file_path);
    }
    size_t map_size = my_map.size();
    ofs.write(reinterpret_cast<const char*>(&map_size), sizeof(map_size));
    for (const auto& kv : my_map) {
        const auto& key = kv.first;
        const auto& value = kv.second;

        // 写入键的大小和内容
        size_t key_size = key.size();
        ofs.write(reinterpret_cast<const char*>(&key_size), sizeof(key_size));
        ofs.write(key.data(), key_size);

        // 写入值的大小和内容
        size_t vector_size = value.size();
        ofs.write(reinterpret_cast<const char*>(&vector_size), sizeof(vector_size));
        ofs.write(reinterpret_cast<const char*>(value.data()), vector_size * sizeof(int));
    }
}
void ReadMyMapFromFile(unordered_map<string, vector<int>>& my_map, const string& file_path) {
    std::ifstream ifs(file_path, std::ios::binary);
    if (!ifs) {
        throw std::runtime_error("Error opening file " + file_path);
    }
    size_t map_size;
    ifs.read(reinterpret_cast<char*>(&map_size), sizeof(map_size));
    for (size_t i = 0; i < map_size; ++i) {
        std::vector<char> buffer;
        size_t vector_size;
        size_t key_size;
        ifs.read(reinterpret_cast<char*>(&key_size), sizeof(int));
        ifs.read(reinterpret_cast<char*>(&vector_size), sizeof(int));
        cout << vector_size << endl;
        cout << key_size << endl;
        buffer.resize(key_size); 
        cout << key_size << endl;
        ifs.read(reinterpret_cast<char*>(buffer.data()), key_size); //这句有问题
        std::string key(buffer.data());
        ifs.read(reinterpret_cast<char*>(&vector_size), sizeof(int));
        vector<int> value;
        int a;
        for (int j = 0; j < vector_size; ++j) {
            ifs.read(reinterpret_cast<char*>(&a), sizeof(int));
            value.push_back(a);
        }
        my_map[key] = value;
    }
}
void search3() {
    vector<Line> lines;
    vector<polygon> polygons;
    MysqlConn conn;
    conn.connect("root", "Ssy2000226..", "test_db", "localhost");
    int idarr_arr[][3] = { {6813, 13128, 3914}, {17984, 14774, 28101}, {17928, 5537, 2980}, {12021, 31902, 2404}, {4917, 4916, 22382}, {17305, 13452, 1701}, {13402, 29334, 15747}, {7688, 11578, 17181}, {10124, 20843, 11949}, {3634, 19230, 2930}, {22214, 14737, 24794}, {5864, 6897, 3020}, {16480, 13862, 2470}, {1574, 31898, 28323}, {22109, 22085, 28007}, {6799, 31167, 22187}, {1021, 2486, 848}, {24649, 27321, 15355}, {4372, 19397, 12491}, {12473, 6553, 11351}, {13557, 22306, 3691}, {22889, 31107, 19632}, {3938, 3943, 310}, {29429, 26161, 23714}, {14435, 22100, 14434}, {6623, 28821, 17644}, {26006, 23994, 28795}, {488, 15537, 14797}, {8155, 24076, 14749}, {25247, 21871, 20264}, {3429, 10115, 15112}, {4425, 29156, 4402}, {15654, 12404, 22081}, {23985, 24275, 8212}, {9850, 25383, 25994}, {10214, 30389, 26838}, {24905, 13940, 25202}, {7231, 13105, 13094}, {741, 30443, 6679}, {13470, 7080, 6216}, {22374, 14507, 12966}, {27173, 26300, 16172}, {17749, 1503, 19922}, {15319, 17839, 7554}, {15718, 15338, 18421}, {15930, 25262, 10223}, {1347, 26351, 26838}, {19435, 25969, 14926}, {15560, 25857, 2717}, {18558, 20255, 19618}, {30393, 30832, 28399}, {27960, 28590, 10472}, {30417, 1505, 18680}, {7736, 24961, 17853}, {11195, 10677, 14700}, {10557, 27839, 9181}, {11157, 19309, 4709}, {17874, 28822, 2177}, {21869, 27139, 6066}, {13479, 16613, 4683}, {28999, 24842, 16087}, {1878, 20116, 20741}, {3675, 17868, 21639}, {19075, 25116, 5616}, {16320, 4461, 28366}, {26160, 7783, 8253}, {15744, 4736, 13690}, {16261, 22006, 1720}, {12680, 30297, 418}, {29968, 23823, 18957}, {20123, 20631, 6983}, {22315, 20302, 26060}, {8768, 15119, 11235}, {25422, 4291, 11473}, {18863, 12049, 146}, {16160, 2664, 11339}, {27708, 19044, 15882}, {3675, 17868, 21639}, {4560, 13262, 7426}, {28010, 27714, 28998}, {7379, 3617, 30995}, {13452, 17305, 1701}, {11289, 19746, 29350}, {31706, 22969, 13694}, {4147, 20879, 3799}, {20818, 12461, 7334}, {25407, 19678, 18793}, {4284, 7541, 26983}, {24963, 25728, 15390}, {24852, 11208, 20644}, {31286, 10887, 15470}, {26704, 12933, 13223}, {31302, 18648, 31733}, {27470, 12004, 4890}, {24120, 21758, 23286}, {20508, 6074, 16102}, {16251, 7128, 25421}, {13531, 26965, 26867}, {17648, 20228, 3241}, {31446, 884, 20822} };
    int cscount5 = 0;
    int cscount10 = 0;
    int cscount15 = 0;
    int cscount = 0;
    steady_clock::time_point begin = steady_clock::now();
    for (int t = 0; t < 100; ++t) {
        vector<Point> points;
        for (int i = 0; i < 3; ++i) {
            string query = "SELECT xz,yz,type_1 FROM obj_tb WHERE id=" + to_string(idarr_arr[t][i]);
            conn.query(query);
            while (conn.next()) {
                points.push_back(Point(stoi(conn.value(0)), stoi(conn.value(1)), conn.value(2)));
            }
        }
        /*for (int i = 0; i < 3; ++i) {
        cout <<"x:"<< points[i].x <<"y:"<< points[i].y <<"type:"<< points[i].type << endl;
        }
        */
        int maxcount = 0;
        class search search(points, lines, polygons);
        /*class search search(points);*/
        for (auto i = search.Result.begin(); i < min(search.Result.end(), search.Result.begin() + min(1, static_cast<int>(search.Result.size()))); ++i) {
            maxcount = 0;
            for (int m = 0; m < 3; ++m) {
                if (*(i->begin()->begin()) == idarr_arr[t][m]) {
                    maxcount += 1;
                }
                if (*(i->begin()->begin() + 1) == idarr_arr[t][m]) {
                    maxcount += 1;
                }
            }
            for (auto j = i->begin() + 1; j != i->end(); ++j) {
                for (auto k = j->begin(); k != j->end(); ++k) {
                    for (int m = 0; m < 3; ++m) {
                        if (*k == idarr_arr[t][m]) {
                            maxcount += 1;
                        }
                    }
                }
            }
            if (maxcount >= 3) {
                cscount5 += 1;
                break;
            }
        }
        for (auto i = search.Result.begin(); i < min(search.Result.end(), search.Result.begin() + min(5, static_cast<int>(search.Result.size()))); ++i) {
            maxcount = 0;
            for (int m = 0; m < 3; ++m) {
                if (*(i->begin()->begin()) == idarr_arr[t][m]) {
                    maxcount += 1;
                }
                if (*(i->begin()->begin() + 1) == idarr_arr[t][m]) {
                    maxcount += 1;
                }
            }
            for (auto j = i->begin() + 1; j != i->end(); ++j) {
                for (auto k = j->begin(); k != j->end(); ++k) {
                    for (int m = 0; m < 3; ++m) {
                        if (*k == idarr_arr[t][m]) {
                            maxcount += 1;
                        }
                    }
                }
            }
            if (maxcount >= 3) {
                cscount10 += 1;
                break;
            }
        }
        for (auto i = search.Result.begin(); i < min(search.Result.end(), search.Result.begin() + min(10, static_cast<int>(search.Result.size()))); ++i) {
            maxcount = 0;
            for (int m = 0; m < 3; ++m) {
                if (*(i->begin()->begin()) == idarr_arr[t][m]) {
                    maxcount += 1;
                }
                if (*(i->begin()->begin() + 1) == idarr_arr[t][m]) {
                    maxcount += 1;
                }
            }
            for (auto j = i->begin() + 1; j != i->end(); ++j) {
                for (auto k = j->begin(); k != j->end(); ++k) {
                    for (int m = 0; m < 3; ++m) {
                        if (*k == idarr_arr[t][m]) {
                            maxcount += 1;
                        }
                    }
                }
            }
            if (maxcount >= 3) {
                cscount15 += 1;
                break;
            }
        }
        for (auto i = search.Result.begin(); i < search.Result.end(); ++i) {
            maxcount = 0;
            for (int m = 0; m < 3; ++m) {
                if (*(i->begin()->begin()) == idarr_arr[t][m]) {
                    maxcount += 1;
                }
                if (*(i->begin()->begin() + 1) == idarr_arr[t][m]) {
                    maxcount += 1;
                }
            }
            for (auto j = i->begin() + 1; j != i->end(); ++j) {
                for (auto k = j->begin(); k != j->end(); ++k) {
                    for (int m = 0; m < 3; ++m) {
                        if (*k == idarr_arr[t][m]) {
                            maxcount += 1;
                        }
                    }
                }
            }
            if (maxcount >= 3) {
                cscount += 1;
                break;
            }
        }
    }
    cout << cscount5 << "\\" << cscount10 << "\\" << cscount15 << "\\"  << cscount << endl;
    steady_clock::time_point end = steady_clock::now();
    auto length = end - begin;
    cout << "耗时:" << length.count() / 1000000 << "毫秒" << endl;
}
void search4() {
    vector<Line> lines;
    vector<polygon> polygons;
    MysqlConn conn;
    conn.connect("root", "Ssy2000226..", "test_db", "localhost");
    int idarr_arr[][4] = { {27635, 10183, 26383, 6531}, {2129, 27451, 19265, 25051}, {29171, 17358, 16260, 4856}, {7851, 17056, 11730, 18507}, {18970, 11028, 31533, 2916}, {23968, 20013, 26456, 23707}, {25062, 31427, 35, 14303}, {20083, 12578, 24945, 12802}, {17473, 15686, 7980, 3984}, {12920, 30636, 22314, 8148}, {13477, 28377, 23840, 7688}, {4574, 16107, 21320, 22991}, {14860, 27077, 10408, 7674}, {10529, 1852, 20760, 26901}, {25119, 29870, 20755, 6069}, {7078, 3465, 25005, 29217}, {224, 21001, 16105, 30551}, {3286, 11052, 19913, 24492}, {29228, 28707, 18611, 30905}, {12033, 27752, 7508, 24719}, {28969, 8274, 16971, 11144}, {26183, 16079, 3719, 21368}, {4340, 16378, 19991, 2321}, {14501, 15527, 28629, 21406}, {5077, 9311, 21006, 30339}, {1694, 5928, 26257, 10058}, {31618, 20764, 7839, 7059}, {15163, 26695, 23539, 17016}, {31352, 645, 18399, 18705}, {26705, 11437, 8112, 26347}, {19930, 6, 20695, 26611}, {6444, 13893, 31026, 14635}, {30039, 13294, 29570, 11311}, {4416, 15285, 2876, 12494}, {23864, 1321, 17898, 3685}, {19265, 24740, 4128, 18473}, {28443, 24817, 3455, 25027}, {23036, 10462, 26277, 15267}, {27564, 25540, 26185, 22869}, {1601, 26, 10916, 18490}, {3141, 72, 8992, 20019}, {18487, 14110, 31710, 10041}, {25799, 2512, 16814, 21183}, {28665, 19665, 27421, 25119}, {19700, 31928, 23803, 30967}, {25035, 25018, 11741, 16463}, {9845, 2606, 12805, 4350}, {19294, 10249, 19688, 22981}, {19216, 8227, 16353, 1471}, {6220, 30683, 28549, 16147}, {26167, 30865, 24225, 1931}, {30761, 18857, 13022, 9867}, {17779, 31395, 21038, 22203}, {7239, 24197, 12317, 16977}, {15118, 27367, 13633, 5365}, {30836, 26843, 456, 4828}, {14855, 20539, 13835, 13004}, {8873, 4545, 8195, 20604}, {23958, 3871, 9238, 14784}, {25861, 21922, 30162, 8222}, {14693, 15891, 9452, 24939}, {26862, 22040, 15904, 16987}, {7214, 7208, 30357, 3120}, {32126, 8115, 19875, 32107}, {19756, 18130, 8755, 29375}, {16570, 4683, 28171, 25646}, {19970, 7434, 7506, 673}, {30500, 25555, 8013, 3021}, {9872, 19179, 13218, 14202}, {6901, 6645, 5930, 28399}, {8721, 19963, 12045, 9061}, {27978, 1464, 18924, 8564}, {22123, 17080, 26157, 20903}, {3115, 4803, 11403, 10492}, {23421, 3584, 5175, 11327}, {17268, 10761, 12335, 28671}, {31176, 30716, 10787, 825}, {3435, 27166, 15833, 22559}, {20500, 14855, 8841, 14353}, {1767, 22441, 12832, 28339}, {6042, 24333, 22257, 16166}, {9149, 7655, 16732, 505}, {1262, 28981, 15116, 12121}, {8094, 18973, 5529, 17318}, {6099, 10519, 10546, 7941}, {24200, 13424, 20520, 7495}, {7895, 8042, 17564, 8654}, {18240, 2044, 29773, 17796}, {21097, 22446, 2802, 31498}, {21612, 21629, 19127, 31029}, {3842, 24014, 14273, 4436}, {5667, 23088, 24353, 16493}, {20504, 23485, 14975, 15022}, {17220, 1338, 710, 14489}, {2009, 12509, 21491, 735}, {17167, 7780, 24807, 25128}, {16937, 1070, 29197, 4768}, {15382, 25856, 5316, 31556}, {20742, 30568, 9913, 31651}, {14424, 28986, 29432, 29001} };
    int cscount5 = 0;
    int cscount10 = 0;
    int cscount15 = 0;
    int cscount = 0;
    steady_clock::time_point begin = steady_clock::now();
    for (int t = 0; t < 100; ++t) {
        vector<Point> points;
        for (int i = 0; i < 4; ++i) {
            string query = "SELECT xz,yz,type_1 FROM obj_tb WHERE id=" + to_string(idarr_arr[t][i]);
            //cout << idarr_arr[t][i] << "\\";
            conn.query(query);
            while (conn.next()) {
                points.push_back(Point(stoi(conn.value(0)), stoi(conn.value(1)), conn.value(2)));
            }
        }
        /*for (int i = 0; i < 3; ++i) {
        cout <<"x:"<< points[i].x <<"y:"<< points[i].y <<"type:"<< points[i].type << endl;
        }
        */
        int maxcount = 0;
        class search search(points, lines, polygons);
        /*class search search(points);*/
        for (auto i = search.Result.begin(); i < min(search.Result.end(), search.Result.begin() + min(1, static_cast<int>(search.Result.size()))); ++i) {
            maxcount = 0;
            for (int m = 0; m < 4; ++m) {
                if (*(i->begin()->begin()) == idarr_arr[t][m]) {
                    maxcount += 1;
                }
                if (*(i->begin()->begin() + 1) == idarr_arr[t][m]) {
                    maxcount += 1;
                }
            }
            for (auto j = i->begin() + 1; j != i->end(); ++j) {
                for (auto k = j->begin(); k != j->end(); ++k) {
                    for (int m = 0; m < 4; ++m) {
                        if (*k == idarr_arr[t][m]) {
                            maxcount += 1;
                        }
                    }
                }
            }
            if (maxcount >= 4) {
                cscount5 += 1;
                break;
            }
        }
        for (auto i = search.Result.begin(); i < min(search.Result.end(), search.Result.begin() + min(5, static_cast<int>(search.Result.size()))); ++i) {
            maxcount = 0;
            for (int m = 0; m < 4; ++m) {
                if (*(i->begin()->begin()) == idarr_arr[t][m]) {
                    maxcount += 1;
                }
                if (*(i->begin()->begin() + 1) == idarr_arr[t][m]) {
                    maxcount += 1;
                }
            }
            for (auto j = i->begin() + 1; j != i->end(); ++j) {
                for (auto k = j->begin(); k != j->end(); ++k) {
                    for (int m = 0; m < 4; ++m) {
                        if (*k == idarr_arr[t][m]) {
                            maxcount += 1;
                        }
                    }
                }
            }
            if (maxcount >= 4) {
                cscount10 += 1;
                break;
            }
        }
        for (auto i = search.Result.begin(); i < min(search.Result.end(), search.Result.begin() + min(10, static_cast<int>(search.Result.size()))); ++i) {
            maxcount = 0;
            for (int m = 0; m < 4; ++m) {
                if (*(i->begin()->begin()) == idarr_arr[t][m]) {
                    maxcount += 1;
                }
                if (*(i->begin()->begin() + 1) == idarr_arr[t][m]) {
                    maxcount += 1;
                }
            }
            for (auto j = i->begin() + 1; j != i->end(); ++j) {
                for (auto k = j->begin(); k != j->end(); ++k) {
                    for (int m = 0; m < 4; ++m) {
                        if (*k == idarr_arr[t][m]) {
                            maxcount += 1;
                        }
                    }
                }
            }
            if (maxcount >= 4) {
                cscount15 += 1;
                break;
            }
        }
        for (auto i = search.Result.begin(); i < search.Result.end(); ++i) {
            maxcount = 0;
            for (int m = 0; m < 4; ++m) {
                if (*(i->begin()->begin()) == idarr_arr[t][m]) {
                    maxcount += 1;
                }
                if (*(i->begin()->begin() + 1) == idarr_arr[t][m]) {
                    maxcount += 1;
                }
            }
            for (auto j = i->begin() + 1; j != i->end(); ++j) {
                for (auto k = j->begin(); k != j->end(); ++k) {
                    for (int m = 0; m < 4; ++m) {
                        if (*k == idarr_arr[t][m]) {
                            maxcount += 1;
                        }
                    }
                }
            }
            if (maxcount >= 4) {
                cscount += 1;
                break;
            }
        }
    }
    cout << cscount5 << "\\" << cscount10 << "\\" << cscount15 << "\\" << cscount << endl;
    steady_clock::time_point end = steady_clock::now();
    auto length = end - begin;
    cout << "耗时:" << length.count() / 1000000 << "毫秒" << endl;
}
void search5() {
    vector<Line> lines;
    vector<polygon> polygons;
    MysqlConn conn;
    conn.connect("root", "Ssy2000226..", "test_db", "localhost");
    int idarr_arr[][5] = { {2348, 11557, 8962, 10132, 17708}, {807, 12961, 11513, 3534, 7333}, {7205, 17958, 8728, 6078, 13603}, {25864, 11897, 27627, 27233, 12308}, {23160, 7469, 28798, 12711, 2057}, {14571, 3371, 21032, 279, 1098}, {28586, 6956, 20164, 26940, 26455}, {645, 11707, 31117, 22672, 30847}, {3933, 7937, 7948, 3939, 7099}, {644, 1622, 746, 697, 17535}, {11796, 254, 5150, 30957, 37}, {1080, 6604, 2498, 4403, 1213}, {19484, 19539, 27363, 14925, 4526}, {28519, 7483, 2902, 24370, 14092}, {13361, 7131, 16916, 27097, 17954}, {8924, 9974, 25188, 14292, 4437}, {26670, 4506, 5716, 980, 22202}, {17224, 4877, 2429, 14605, 16955}, {25505, 17673, 27047, 2695, 23808}, {5722, 10230, 12582, 6728, 10135}, {13315, 20169, 2742, 1863, 26594}, {12833, 26583, 12159, 14208, 9054}, {26230, 20360, 23693, 13024, 20706}, {29154, 19988, 16512, 6395, 12393}, {20416, 20689, 16738, 263, 14694}, {27338, 12528, 1100, 15912, 24424}, {12819, 2518, 15209, 13570, 20019}, {27624, 29543, 21317, 16710, 11031}, {30717, 1715, 26509, 5625, 24557}, {16927, 6115, 19517, 30056, 22183}, {26792, 8823, 8863, 12172, 136}, {1674, 19927, 21356, 19851, 4847}, {4960, 24455, 28392, 12266, 26475}, {1623, 5361, 16890, 18382, 30372}, {5763, 16080, 28868, 18296, 28899}, {2100, 903, 22130, 13722, 22831}, {15150, 26986, 17908, 25368, 27272}, {30198, 30174, 27503, 30886, 30177}, {7826, 10506, 1340, 30613, 24679}, {1694, 135, 2435, 25031, 25527}, {30871, 24248, 27420, 14703, 27802}, {17544, 20114, 30370, 20838, 25559}, {23238, 3155, 12350, 5526, 5268}, {10730, 17741, 21807, 28477, 12010}, {7172, 18205, 5896, 19740, 27862}, {9954, 10502, 25884, 7419, 25885}, {24887, 1536, 21672, 5437, 6842}, {9776, 3131, 22985, 3121, 3145}, {10878, 5967, 21214, 21002, 23706}, {11591, 4279, 30019, 9579, 26341}, {2679, 12861, 15472, 9329, 11996}, {11598, 10325, 18165, 4441, 15856}, {20397, 11370, 16136, 11373, 9896}, {30941, 23614, 6917, 20515, 22464}, {5756, 28599, 25950, 28359, 12964}, {24852, 11208, 20644, 6574, 27919}, {20507, 28746, 1235, 15420, 13566}, {12479, 948, 15707, 30820, 3033}, {14940, 27208, 7365, 19474, 4956}, {17306, 14564, 9637, 9253, 8327}, {8858, 5498, 9906, 31712, 460}, {10177, 21314, 20595, 24609, 23275}, {12587, 15623, 21882, 17040, 3769}, {29265, 30670, 21149, 22278, 7107}, {1344, 30458, 26322, 7288, 3400}, {19453, 19600, 24904, 29720, 21913}, {25197, 23557, 14552, 2187, 356}, {9931, 17509, 20211, 740, 21907}, {7965, 30510, 6386, 11618, 17649}, {22355, 20763, 20388, 24323, 25919}, {14422, 6910, 16111, 7421, 23665}, {3683, 10130, 26762, 10018, 4240}, {2982, 12611, 11577, 5804, 23010}, {1013, 12306, 1014, 12307, 541}, {12261, 15058, 21907, 9917, 9931}, {4256, 9174, 24909, 29591, 6898}, {9381, 6171, 2322, 873, 28008}, {20345, 28753, 16639, 804, 24601}, {6847, 25851, 21982, 2038, 19139}, {10328, 17190, 12573, 25840, 24919}, {22358, 20161, 8979, 4141, 901}, {13934, 27369, 13870, 22353, 2445}, {31125, 14482, 15576, 24933, 2159}, {10296, 16997, 14307, 12719, 12977}, {1679, 27642, 13540, 18985, 1199}, {30241, 31769, 18118, 14630, 23503}, {2240, 20614, 10243, 5979, 24223}, {1884, 9203, 31709, 1682, 19194}, {29349, 30567, 13074, 23455, 23859}, {28336, 28491, 29641, 26037, 649}, {21778, 2666, 22516, 25316, 24993}, {16283, 4268, 13852, 3745, 16415}, {20102, 13089, 6935, 3196, 4810}, {5744, 24841, 25705, 23779, 13426}, {13486, 17258, 17257, 23192, 1856}, {26510, 29787, 29453, 19257, 7116}, {19694, 16296, 13977, 23896, 11190}, {5637, 27088, 13812, 7889, 8832}, {29601, 2757, 9935, 11650, 12298}, {29161, 23509, 2403, 11292, 12798} };
    int cscount5 = 0;
    int cscount10 = 0;
    int cscount15 = 0;
    int cscount = 0;
    steady_clock::time_point begin = steady_clock::now();
    for (int t = 0; t < 100; ++t) {
        vector<Point> points;
        for (int i = 0; i < 5; ++i) {
            string query = "SELECT xz,yz,type_1 FROM obj_tb WHERE id=" + to_string(idarr_arr[t][i]);
            //cout << idarr_arr[t][i] << "\\";
            conn.query(query);
            while (conn.next()) {
                points.push_back(Point(stoi(conn.value(0)), stoi(conn.value(1)), conn.value(2)));
            }
        }
        /*for (int i = 0; i < 3; ++i) {
        cout <<"x:"<< points[i].x <<"y:"<< points[i].y <<"type:"<< points[i].type << endl;
        }
        */
        int maxcount = 0;
        class search search(points, lines, polygons);
        /*class search search(points);*/
        for (auto i = search.Result.begin(); i < min(search.Result.end(), search.Result.begin() + min(1, static_cast<int>(search.Result.size()))); ++i) {
            maxcount = 0;
            for (int m = 0; m < 5; ++m) {
                if (*(i->begin()->begin()) == idarr_arr[t][m]) {
                    maxcount += 1;
                }
                if (*(i->begin()->begin() + 1) == idarr_arr[t][m]) {
                    maxcount += 1;
                }
            }
            for (auto j = i->begin() + 1; j != i->end(); ++j) {
                for (auto k = j->begin(); k != j->end(); ++k) {
                    for (int m = 0; m < 5; ++m) {
                        if (*k == idarr_arr[t][m]) {
                            maxcount += 1;
                        }
                    }
                }
            }
            if (maxcount >= 5) {
                cscount5 += 1;
                break;
            }
        }
        for (auto i = search.Result.begin(); i < min(search.Result.end(), search.Result.begin() + min(5, static_cast<int>(search.Result.size()))); ++i) {
            maxcount = 0;
            for (int m = 0; m < 5; ++m) {
                if (*(i->begin()->begin()) == idarr_arr[t][m]) {
                    maxcount += 1;
                }
                if (*(i->begin()->begin() + 1) == idarr_arr[t][m]) {
                    maxcount += 1;
                }
            }
            for (auto j = i->begin() + 1; j != i->end(); ++j) {
                for (auto k = j->begin(); k != j->end(); ++k) {
                    for (int m = 0; m < 5; ++m) {
                        if (*k == idarr_arr[t][m]) {
                            maxcount += 1;
                        }
                    }
                }
            }
            if (maxcount >= 5) {
                cscount10 += 1;
                break;
            }
        }
        for (auto i = search.Result.begin(); i < min(search.Result.end(), search.Result.begin() + min(10, static_cast<int>(search.Result.size()))); ++i) {
            maxcount = 0;
            for (int m = 0; m < 5; ++m) {
                if (*(i->begin()->begin()) == idarr_arr[t][m]) {
                    maxcount += 1;
                }
                if (*(i->begin()->begin() + 1) == idarr_arr[t][m]) {
                    maxcount += 1;
                }
            }
            for (auto j = i->begin() + 1; j != i->end(); ++j) {
                for (auto k = j->begin(); k != j->end(); ++k) {
                    for (int m = 0; m < 5; ++m) {
                        if (*k == idarr_arr[t][m]) {
                            maxcount += 1;
                        }
                    }
                }
            }
            if (maxcount >= 5) {
                cscount15 += 1;
                break;
            }
        }
        for (auto i = search.Result.begin(); i < search.Result.end(); ++i) {
            maxcount = 0;
            for (int m = 0; m < 5; ++m) {
                if (*(i->begin()->begin()) == idarr_arr[t][m]) {
                    maxcount += 1;
                }
                if (*(i->begin()->begin() + 1) == idarr_arr[t][m]) {
                    maxcount += 1;
                }
            }
            for (auto j = i->begin() + 1; j != i->end(); ++j) {
                for (auto k = j->begin(); k != j->end(); ++k) {
                    for (int m = 0; m < 5; ++m) {
                        if (*k == idarr_arr[t][m]) {
                            maxcount += 1;
                        }
                    }
                }
            }
            if (maxcount >= 5) {
                cscount += 1;
                break;
            }
        }
    }
    cout << cscount5 << "\\" << cscount10 << "\\" << cscount15 << "\\" <<  cscount << endl;
    steady_clock::time_point end = steady_clock::now();
    auto length = end - begin;
    cout << "耗时:" << length.count() / 1000000 << "毫秒" << endl;
}
void search7() {
    vector<Line> lines;
    vector<polygon> polygons;
    MysqlConn conn;
    conn.connect("root", "Ssy2000226..", "test_db", "localhost");
    int idarr_arr[][7] = { {12524, 31790, 30602, 16844, 19792, 17611, 4565}, {30080, 1479, 11622, 288, 16287, 30039, 17222}, {17378, 11272, 1923, 13679, 28206, 18494, 13704}, {21220, 22237, 22239, 4123, 22360, 29865, 21439}, {20038, 20205, 3087, 3050, 22466, 29229, 29236}, {5014, 27764, 520, 5015, 1330, 993, 15956}, {25617, 15397, 2801, 19989, 13147, 3074, 1294}, {7236, 7238, 7235, 4733, 6192, 14277, 19432}, {28886, 29662, 26535, 20524, 27929, 29854, 594}, {17644, 28821, 6623, 9024, 31664, 29581, 8145}, {29703, 22208, 3789, 13395, 25979, 7157, 2634}, {19155, 6179, 14165, 27351, 30286, 18746, 26664}, {18221, 2956, 805, 31764, 1947, 27264, 28203}, {15894, 31273, 19638, 29569, 931, 2199, 2662}, {659, 9056, 28319, 13238, 12388, 20012, 15071}, {25568, 25388, 30471, 12664, 29927, 19507, 23881}, {28087, 6212, 25868, 23026, 3474, 3603, 27997}, {12980, 12563, 1498, 9246, 28211, 14572, 2331}, {10541, 9601, 10631, 11567, 23947, 21303, 2141}, {5779, 27186, 16232, 8437, 29487, 861, 27184}, {38, 3551, 8, 5791, 30936, 7474, 1689}, {29616, 4857, 31389, 2784, 30657, 31890, 30653}, {14053, 14056, 5906, 14054, 12259, 29768, 12802}, {28278, 20953, 12002, 19564, 20963, 23730, 14463}, {84, 31122, 19839, 15330, 11333, 2557, 4566}, {13230, 5461, 10396, 8974, 16364, 27711, 13002}, {22004, 31953, 29332, 8989, 2882, 6062, 25322}, {7142, 24186, 19913, 22959, 29264, 23396, 22512}, {30430, 11540, 30432, 13099, 18588, 5171, 28460}, {25370, 5462, 15837, 5966, 20802, 28317, 29781}, {14212, 10392, 5536, 5703, 4849, 18658, 759}, {32110, 3049, 10298, 14764, 23004, 14324, 24522}, {10228, 6794, 17074, 17449, 20727, 11563, 14041}, {26660, 15779, 9633, 13714, 15552, 14017, 12834}, {9873, 23924, 32020, 12270, 19754, 28965, 15655}, {13891, 9492, 23474, 17473, 29829, 6147, 14257}, {648, 10733, 20516, 30860, 758, 5743, 4908}, {4010, 8646, 18226, 25621, 2211, 25376, 9523}, {4254, 7989, 19319, 11612, 14441, 2285, 11706}, {13487, 17259, 13941, 12237, 10342, 14433, 19706}, {19028, 16753, 31253, 7283, 1985, 15166, 17347}, {3974, 27582, 4652, 28786, 8824, 682, 15641}, {23170, 5368, 24750, 20904, 18666, 5928, 21522}, {8487, 8489, 22145, 28198, 7908, 29975, 27080}, {20273, 22407, 22724, 10836, 21208, 22878, 19350}, {8804, 10200, 4433, 11099, 4367, 12994, 4841}, {29780, 19191, 24691, 29922, 15751, 27695, 6841}, {14246, 10436, 26097, 14263, 3925, 7834, 14348}, {12943, 13041, 12689, 23712, 9853, 7972, 15443}, {30402, 30414, 15870, 16078, 9791, 10323, 16363}, {21470, 16311, 29926, 5737, 11391, 14496, 9484}, {23005, 9875, 28676, 19421, 29037, 30046, 17376}, {22297, 8264, 2009, 7691, 13158, 20185, 7059}, {25646, 4073, 25432, 10070, 18903, 28171, 17892}, {10367, 25250, 9892, 7503, 4574, 1245, 28542}, {16047, 16064, 14385, 13267, 10208, 10928, 10883}, {31627, 31873, 29559, 21716, 18599, 13901, 13900}, {24998, 8380, 8653, 4030, 3793, 23398, 19814}, {6249, 23438, 6248, 19483, 6245, 12779, 24418}, {25057, 27761, 1190, 18669, 5562, 12656, 30919}, {20931, 26110, 16128, 6266, 15215, 12547, 29303}, {10454, 5945, 26207, 17448, 7275, 18917, 9686}, {6287, 9103, 12262, 21746, 5929, 5364, 19994}, {15621, 18007, 24605, 13184, 3122, 23666, 26732}, {23722, 9773, 5326, 5709, 21259, 14312, 24795}, {15456, 5773, 5774, 14124, 16849, 19730, 5775}, {12221, 3782, 12462, 3781, 8720, 6808, 6123}, {31960, 26176, 22056, 17986, 29597, 18797, 27842}, {22427, 2239, 3839, 1397, 22601, 22604, 2691}, {15087, 29033, 11071, 28767, 9681, 19037, 28364}, {29276, 13594, 20599, 13220, 26736, 29793, 26626}, {7721, 17668, 28419, 25381, 30870, 27094, 27906}, {13185, 29589, 16328, 22187, 27318, 23666, 22677}, {22469, 6222, 29309, 10863, 22216, 9404, 12499}, {29650, 26776, 20545, 6703, 25810, 27615, 16729}, {17217, 10452, 13929, 18202, 7492, 29518, 23149}, {5336, 26429, 12663, 23437, 23150, 27017, 12598}, {13942, 71, 14722, 23246, 17580, 12675, 17738}, {29892, 27680, 16132, 17078, 16254, 8244, 17748}, {14330, 17176, 7973, 21964, 11452, 17435, 2951}, {32006, 11896, 19806, 25666, 26344, 20590, 2746}, {14869, 20220, 16466, 6656, 7855, 16686, 9318}, {12839, 13582, 27496, 14823, 28812, 28438, 7300}, {19247, 25638, 30211, 13914, 7979, 15821, 29580}, {20822, 884, 31446, 18204, 1277, 21900, 13473}, {19623, 24111, 11852, 18913, 206, 10384, 1868}, {15749, 9355, 9550, 14584, 18189, 19480, 6695}, {13272, 19883, 13600, 24689, 21695, 31516, 23725}, {27689, 21575, 13040, 14743, 11441, 3183, 4267}, {6604, 2498, 21353, 2401, 1080, 16246, 20176}, {16411, 22162, 1544, 11197, 12408, 886, 11315}, {26836, 26837, 28603, 2265, 1956, 1843, 31207}, {26900, 26897, 13930, 6181, 26894, 19497, 26405}, {21218, 20210, 30607, 17093, 26242, 29597, 7730}, {19466, 18591, 11242, 6852, 21835, 25362, 19224}, {2043, 7434, 36, 23296, 16781, 28295, 5656}, {5760, 22134, 12085, 25035, 15627, 12697, 2687}, {3439, 26055, 2605, 6336, 22836, 22647, 23078}, {2203, 31431, 12151, 9634, 10954, 31249, 24646}, {31110, 5136, 22824, 14599, 13425, 6830, 29372} };
    int cscount5 = 0;
    int cscount10 = 0;
    int cscount15 = 0;
    int cscount = 0;
    steady_clock::time_point begin = steady_clock::now();
    for (int t = 0; t < 100; ++t) {
        vector<Point> points;
        for (int i = 0; i < 7; ++i) {
            //cout << idarr_arr[t][i] << "\\";
            string query = "SELECT xz,yz,type_1 FROM obj_tb WHERE id=" + to_string(idarr_arr[t][i]);
            conn.query(query);
            while (conn.next()) {
                points.push_back(Point(stoi(conn.value(0)), stoi(conn.value(1)), conn.value(2)));
            }
        }
        /*for (int i = 0; i < 3; ++i) {
        cout <<"x:"<< points[i].x <<"y:"<< points[i].y <<"type:"<< points[i].type << endl;
        }
        */
        int maxcount = 0;
        class search search(points, lines, polygons);
        /*class search search(points);*/
        for (auto i = search.Result.begin(); i < min(search.Result.end(), search.Result.begin() + min(1, static_cast<int>(search.Result.size()))); ++i) {
            maxcount = 0;
            for (int m = 0; m < 7; ++m) {
                if (*(i->begin()->begin()) == idarr_arr[t][m]) {
                    maxcount += 1;
                }
                if (*(i->begin()->begin() + 1) == idarr_arr[t][m]) {
                    maxcount += 1;
                }
            }
            for (auto j = i->begin() + 1; j != i->end(); ++j) {
                for (auto k = j->begin(); k != j->end(); ++k) {
                    for (int m = 0; m < 7; ++m) {
                        if (*k == idarr_arr[t][m]) {
                            maxcount += 1;
                        }
                    }
                }
            }
            if (maxcount >= 7) {
                cscount5 += 1;
                break;
            }
        }
        for (auto i = search.Result.begin(); i < min(search.Result.end(), search.Result.begin() + min(5, static_cast<int>(search.Result.size()))); ++i) {
            maxcount = 0;
            for (int m = 0; m < 7; ++m) {
                if (*(i->begin()->begin()) == idarr_arr[t][m]) {
                    maxcount += 1;
                }
                if (*(i->begin()->begin() + 1) == idarr_arr[t][m]) {
                    maxcount += 1;
                }
            }
            for (auto j = i->begin() + 1; j != i->end(); ++j) {
                for (auto k = j->begin(); k != j->end(); ++k) {
                    for (int m = 0; m < 7; ++m) {
                        if (*k == idarr_arr[t][m]) {
                            maxcount += 1;
                        }
                    }
                }
            }
            if (maxcount >= 7) {
                cscount10 += 1;
                break;
            }
        }
        for (auto i = search.Result.begin(); i < min(search.Result.end(), search.Result.begin() + min(10, static_cast<int>(search.Result.size()))); ++i) {
            maxcount = 0;
            for (int m = 0; m < 7; ++m) {
                if (*(i->begin()->begin()) == idarr_arr[t][m]) {
                    maxcount += 1;
                }
                if (*(i->begin()->begin() + 1) == idarr_arr[t][m]) {
                    maxcount += 1;
                }
            }
            for (auto j = i->begin() + 1; j != i->end(); ++j) {
                for (auto k = j->begin(); k != j->end(); ++k) {
                    for (int m = 0; m < 7; ++m) {
                        if (*k == idarr_arr[t][m]) {
                            maxcount += 1;
                        }
                    }
                }
            }
            if (maxcount >= 7) {
                cscount15 += 1;
                break;
            }
        }
        for (auto i = search.Result.begin(); i < search.Result.end(); ++i) {
            maxcount = 0;
            for (int m = 0; m < 7; ++m) {
                if (*(i->begin()->begin()) == idarr_arr[t][m]) {
                    maxcount += 1;
                }
                if (*(i->begin()->begin() + 1) == idarr_arr[t][m]) {
                    maxcount += 1;
                }
            }
            for (auto j = i->begin() + 1; j != i->end(); ++j) {
                for (auto k = j->begin(); k != j->end(); ++k) {
                    for (int m = 0; m < 7; ++m) {
                        if (*k == idarr_arr[t][m]) {
                            maxcount += 1;
                        }
                    }
                }
            }
            if (maxcount >= 7) {
                cscount += 1;
                break;
            }
        }
    }
    cout << cscount5 << "\\" << cscount10 << "\\" << cscount15 << "\\" << cscount << endl;
    steady_clock::time_point end = steady_clock::now();
    auto length = end - begin;
    cout << "耗时:" << length.count() / 1000000 << "毫秒" << endl;
}
void search10() {
    vector<Line> lines;
    vector<polygon> polygons;
    MysqlConn conn;
    conn.connect("root", "Ssy2000226..", "test_db", "localhost");
    int idarr_arr[][10] = { {18047, 23316, 22992, 14649, 12642, 10969, 14787, 24844, 5469, 2468}, {14744, 22168, 1355, 28351, 3878, 29943, 29324, 14027, 16898, 14364}, {30782, 9264, 22871, 22350, 23673, 21079, 19447, 22912, 22398, 9433}, {22652, 13203, 29516, 22722, 10559, 26061, 27354, 19071, 6148, 5470}, {14850, 15423, 27928, 23360, 8647, 10587, 17392, 26921, 2441, 6068}, {17486, 30845, 30240, 8084, 1931, 26167, 22682, 2378, 15507, 6706}, {9026, 8521, 29319, 12527, 29774, 30001, 4920, 16372, 6011, 21985}, {23285, 16390, 17110, 2980, 12608, 17928, 5537, 16975, 12075, 9803}, {23306, 847, 19408, 878, 376, 3969, 20610, 23388, 28901, 1920}, {16172, 5704, 20097, 26300, 5712, 7581, 18547, 5721, 15051, 27173}, {27745, 26666, 27490, 27416, 18755, 27718, 22528, 27460, 30140, 21745}, {10249, 28527, 31872, 26915, 12788, 19565, 12719, 12977, 7197, 16997}, {11927, 14677, 9498, 4802, 5567, 29126, 10016, 1990, 9502, 30743}, {8207, 19385, 25090, 24891, 15059, 18899, 27365, 28103, 8535, 1012}, {30868, 15312, 12308, 26721, 27627, 30561, 26560, 25864, 28429, 18395}, {22203, 24471, 20929, 24419, 24387, 24340, 24761, 18635, 22462, 23071}, {24003, 22624, 6545, 12811, 6372, 14188, 19182, 21004, 30614, 1793}, {15177, 15140, 19171, 20103, 22013, 31351, 23347, 28565, 16216, 25495}, {6037, 10147, 9783, 4662, 2735, 27642, 22746, 11505, 432, 4908}, {26903, 540, 2167, 13560, 11073, 8430, 5410, 29377, 12809, 3641}, {27143, 24659, 6155, 19302, 7336, 15777, 6621, 24492, 15954, 25943}, {31640, 5560, 22346, 19337, 14756, 19759, 30774, 3407, 3399, 18262}, {20117, 10355, 8094, 29869, 18973, 23112, 11065, 6989, 10959, 28153}, {24522, 16000, 30841, 16015, 14206, 26358, 13666, 23004, 29834, 16001}, {23042, 24746, 19305, 21235, 22347, 22220, 29574, 24467, 29326, 22444}, {20553, 11116, 1927, 19406, 20377, 3794, 12970, 4471, 11052, 26408}, {17924, 30204, 18457, 12536, 14515, 15103, 3219, 16825, 14836, 14306}, {620, 1434, 1814, 4002, 3127, 4764, 26341, 4952, 3997, 9218}, {7220, 1822, 8073, 7935, 7212, 5570, 8771, 3108, 12114, 9136}, {9695, 2182, 10658, 7276, 9827, 31608, 23961, 3381, 16678, 3358}, {17540, 12713, 20150, 6367, 9283, 1912, 4261, 28716, 17815, 2400}, {26223, 29953, 26467, 26343, 26650, 16152, 16393, 29542, 31060, 30159}, {21118, 12568, 21919, 25586, 16600, 20254, 19498, 22156, 18741, 22728}, {29735, 23810, 16073, 20646, 23659, 6351, 29123, 3447, 27222, 26277}, {13974, 990, 31770, 15895, 19176, 5053, 22787, 28312, 17415, 19554}, {14006, 14007, 23428, 10309, 24467, 22444, 29326, 22347, 5783, 24164}, {1667, 5287, 10473, 5822, 14806, 4482, 6201, 26389, 4445, 24892}, {15812, 29823, 16839, 4708, 4639, 17593, 29189, 17309, 24160, 27874}, {23591, 21245, 3816, 6789, 31511, 23573, 2274, 24249, 9144, 16082}, {31710, 521, 8572, 7729, 10045, 8910, 4177, 18487, 10041, 24326}, {16461, 26026, 19336, 31513, 27736, 11390, 19334, 28032, 31935, 6136}, {12293, 2532, 5382, 1793, 7833, 26340, 27635, 9037, 21744, 16115}, {706, 26192, 8889, 5839, 5659, 3299, 28215, 25593, 5628, 13500}, {18393, 263, 29871, 16738, 14694, 20689, 22760, 26489, 18159, 18462}, {1136, 25862, 32122, 15619, 27870, 15617, 23724, 12014, 12466, 4969}, {148, 24089, 237, 8890, 27350, 19605, 20048, 13632, 22021, 8794}, {21232, 30881, 30252, 30254, 19208, 5917, 15096, 2920, 29534, 7443}, {22481, 1419, 6884, 10049, 24019, 10756, 24482, 11517, 16530, 2142}, {10231, 30458, 16583, 3400, 31833, 24678, 26322, 6770, 7288, 1344}, {19722, 8549, 19046, 23255, 10694, 4446, 8307, 15928, 15810, 24688}, {24662, 14788, 23720, 13464, 3366, 17422, 30231, 9040, 20616, 2083}, {29626, 5233, 6752, 7917, 22508, 25490, 31943, 8144, 11084, 945}, {7898, 12796, 4275, 7560, 11528, 5377, 30739, 16777, 9521, 17518}, {25733, 20932, 26523, 14631, 30484, 22267, 9760, 16832, 1559, 30513}, {26527, 21847, 28592, 9516, 20853, 25754, 9739, 22086, 10021, 20357}, {2625, 473, 22637, 21560, 22589, 93, 31287, 29769, 31282, 19603}, {10643, 6844, 14214, 31025, 6360, 713, 10744, 24279, 10768, 18501}, {1212, 1926, 31795, 11259, 25169, 8723, 1597, 1833, 8722, 26074}, {19265, 7520, 4164, 2979, 8016, 25471, 2129, 5183, 5076, 2962}, {25245, 24243, 32130, 31484, 5083, 562, 11810, 27386, 20261, 28889}, {17831, 27403, 22749, 2763, 31880, 6746, 6864, 30651, 27808, 26862}, {7518, 20705, 13768, 30931, 26622, 9739, 25715, 14151, 16916, 17954}, {23175, 29611, 7743, 23198, 26556, 22767, 29789, 27390, 22287, 25279}, {27666, 24541, 29333, 4659, 9843, 12534, 26125, 1164, 1326, 385}, {13659, 10780, 524, 15862, 22269, 19067, 24196, 1049, 25680, 5777}, {9594, 27515, 31076, 1457, 384, 21972, 11508, 8708, 6047, 26648}, {14555, 24313, 18663, 8020, 30334, 17456, 772, 29128, 22470, 8203}, {1176, 6927, 29544, 31824, 20381, 27266, 16039, 30785, 21555, 22012}, {24014, 7995, 24224, 8428, 18299, 23892, 8353, 3747, 31244, 31231}, {15493, 15600, 6705, 14107, 8694, 28275, 5544, 6486, 25675, 22078}, {15156, 13836, 13320, 7493, 18269, 23404, 21370, 12772, 689, 1243}, {6162, 15737, 27049, 22989, 9039, 18145, 16189, 15345, 12871, 29895}, {22365, 18046, 25178, 10924, 19164, 25729, 19165, 26383, 24306, 14297}, {3324, 16694, 26728, 25926, 30987, 15528, 29490, 31084, 11405, 8417}, {29596, 28845, 24989, 28712, 18275, 25340, 29928, 19477, 17093, 27842}, {30296, 19696, 20016, 15854, 15287, 19833, 4312, 15288, 3143, 23788}, {4305, 16741, 21842, 12034, 7314, 12540, 14321, 10174, 2324, 4529}, {9238, 31151, 7076, 24507, 32145, 12080, 30756, 11207, 27132, 19390}, {2252, 1394, 6081, 12821, 707, 5431, 7324, 22917, 16810, 30426}, {29860, 2164, 23639, 25558, 91, 6535, 27152, 21510, 5204, 803}, {26345, 27632, 1217, 14287, 3908, 17702, 1571, 24209, 7197, 31879}, {17045, 731, 23403, 28992, 16352, 605, 27729, 1038, 831, 2569}, {14667, 19950, 26768, 25620, 24383, 7496, 29443, 16564, 14800, 15159}, {30631, 13828, 18163, 280, 28218, 19768, 9738, 9743, 22905, 15548}, {15148, 17737, 14374, 13984, 29989, 18906, 18383, 20191, 30701, 23898}, {12361, 12362, 12360, 9885, 21437, 15622, 3964, 4809, 17040, 15623}, {4791, 6124, 6076, 26299, 24000, 7823, 4792, 14693, 32106, 12320}, {18888, 20836, 12116, 18989, 18248, 21660, 18284, 14192, 8356, 26769}, {27888, 28079, 320, 1319, 27537, 8154, 31703, 6156, 31859, 19716}, {12397, 31371, 12316, 1116, 604, 16083, 13410, 32, 717, 2218}, {30858, 26232, 24450, 24489, 23970, 22669, 15353, 21471, 16153, 15915}, {18579, 11537, 3666, 4347, 21874, 21498, 2042, 8482, 14966, 5241}, {10570, 10042, 7527, 3083, 28217, 28219, 25360, 1061, 607, 19446}, {24836, 32013, 25081, 32016, 32015, 20756, 26451, 1320, 11302, 29784}, {6574, 22770, 20644, 11208, 24852, 15916, 8132, 30914, 27919, 10543}, {29618, 16259, 5086, 16322, 14588, 16519, 10604, 10804, 10872, 19410}, {28357, 22373, 18384, 11956, 28026, 27202, 27744, 19617, 7925, 18302}, {377, 5163, 29513, 461, 7351, 19097, 344, 28532, 15586, 8095}, {19287, 18537, 18564, 18548, 18645, 18566, 19027, 22312, 3848, 22551}, {19231, 9625, 12189, 684, 25299, 20825, 29043, 12100, 3086, 319} };
    int cscount5 = 0;
    int cscount10 = 0;
    int cscount15 = 0;
    int cscount = 0;
    steady_clock::time_point begin = steady_clock::now();
    for (int t = 0; t < 100; ++t) {
        vector<Point> points;
        for (int i = 0; i < 10; ++i) {
            string query = "SELECT xz,yz,type_1 FROM obj_tb WHERE id=" + to_string(idarr_arr[t][i]);
            conn.query(query);
            while (conn.next()) {
                points.push_back(Point(stoi(conn.value(0)), stoi(conn.value(1)), conn.value(2)));
            }
        }
        /*for (int i = 0; i < 3; ++i) {
        cout <<"x:"<< points[i].x <<"y:"<< points[i].y <<"type:"<< points[i].type << endl;
        }
        */
        int maxcount = 0;
        class search search(points, lines, polygons);
        /*class search search(points);*/
        for (auto i = search.Result.begin(); i < min(search.Result.end(), search.Result.begin() + min(1, static_cast<int>(search.Result.size()))); ++i) {
            maxcount = 0;
            for (int m = 0; m < 10; ++m) {
                if (*(i->begin()->begin()) == idarr_arr[t][m]) {
                    maxcount += 1;
                }
                if (*(i->begin()->begin() + 1) == idarr_arr[t][m]) {
                    maxcount += 1;
                }
            }
            for (auto j = i->begin() + 1; j != i->end(); ++j) {
                for (auto k = j->begin(); k != j->end(); ++k) {
                    for (int m = 0; m < 10; ++m) {
                        if (*k == idarr_arr[t][m]) {
                            maxcount += 1;
                        }
                    }
                }
            }
            if (maxcount >= 10) {
                cscount5 += 1;
                break;
            }
        }
        for (auto i = search.Result.begin(); i < min(search.Result.end(), search.Result.begin() + min(5, static_cast<int>(search.Result.size()))); ++i) {
            maxcount = 0;
            for (int m = 0; m < 10; ++m) {
                if (*(i->begin()->begin()) == idarr_arr[t][m]) {
                    maxcount += 1;
                }
                if (*(i->begin()->begin() + 1) == idarr_arr[t][m]) {
                    maxcount += 1;
                }
            }
            for (auto j = i->begin() + 1; j != i->end(); ++j) {
                for (auto k = j->begin(); k != j->end(); ++k) {
                    for (int m = 0; m < 10; ++m) {
                        if (*k == idarr_arr[t][m]) {
                            maxcount += 1;
                        }
                    }
                }
            }
            if (maxcount >= 10) {
                cscount10 += 1;
                break;
            }
        }
        for (auto i = search.Result.begin(); i < min(search.Result.end(), search.Result.begin() + min(10, static_cast<int>(search.Result.size()))); ++i) {
            maxcount = 0;
            for (int m = 0; m < 10; ++m) {
                if (*(i->begin()->begin()) == idarr_arr[t][m]) {
                    maxcount += 1;
                }
                if (*(i->begin()->begin() + 1) == idarr_arr[t][m]) {
                    maxcount += 1;
                }
            }
            for (auto j = i->begin() + 1; j != i->end(); ++j) {
                for (auto k = j->begin(); k != j->end(); ++k) {
                    for (int m = 0; m < 10; ++m) {
                        if (*k == idarr_arr[t][m]) {
                            maxcount += 1;
                        }
                    }
                }
            }
            if (maxcount >= 10) {
                cscount15 += 1;
                break;
            }
        }
        for (auto i = search.Result.begin(); i < search.Result.end(); ++i) {
            maxcount = 0;
            for (int m = 0; m < 10; ++m) {
                if (*(i->begin()->begin()) == idarr_arr[t][m]) {
                    maxcount += 1;
                }
                if (*(i->begin()->begin() + 1) == idarr_arr[t][m]) {
                    maxcount += 1;
                }
            }
            for (auto j = i->begin() + 1; j != i->end(); ++j) {
                for (auto k = j->begin(); k != j->end(); ++k) {
                    for (int m = 0; m < 10; ++m) {
                        if (*k == idarr_arr[t][m]) {
                            maxcount += 1;
                        }
                    }
                }
            }
            if (maxcount >= 10) {
                cscount += 1;
                break;
            }
        }
    }
    cout << cscount5 << "\\" << cscount10 << "\\" << cscount15 << "\\" << cscount << endl;
    steady_clock::time_point end = steady_clock::now();
    auto length = end - begin;
    cout << "耗时:" << length.count() / 1000000 << "毫秒" << endl;
}
int main()
{
    //steady_clock::time_point begin = steady_clock::now();
    //vector<Point> points = {Point(2,15,"公司企业"),Point(7,13,"生活服务"),Point(4,22,"购物服务") };
    //vector<Line> lines = {Line(6,8,19,26)};
    //vector<Point> points1 = { Point(3,5),Point(5,5),Point(5,3),Point(3,3) };
    ////vector<Point> points2 = { Point(9,15),Point(23,25),Point(16,7) };
    //vector<polygon> polygons = { polygon(points1)};
    //class search search(points,lines,polygons);
    //steady_clock::time_point end = steady_clock::now();
    //auto length = end - begin;
    //cout << "耗时:" << length.count() / 1000000 << "毫秒" << endl;
    search3();
    //search4();
    search5();
    search7();
    search10();
    //const int point_size = 3;
    //int rand_point[point_size];
    //srand(time(NULL));
    //for (int i = 0; i < point_size; i++) {
    //    rand_point[i] = rand() % 32170 + 1; // Generate a random number between 1 and 32170
    //}
    //for (int i = 0; i < point_size;++i) {
    //    string query = "SELECT xz,yz,type_1 FROM obj_tb WHERE id=" + to_string(rand_point[i]);
    //    conn.query(query);
    //    while (conn.next()) {
    //        points.push_back(Point(stoi(conn.value(0)), stoi(conn.value(1)), conn.value(2)));
    //    }
    //    
    //}
    //const int line_size = 0;
    //int rand_line[line_size];
    //srand(time(NULL));
    //for (int i = 0; i < line_size; i++) {
    //    rand_line[i] = rand() % 9637 + 1; // Generate a random number between 1 and 9637
    //}
    //for (int i = 0; i < line_size; ++i) {
    //    string query = "SELECT x_first,y_first,x_end,y_end FROM bline_tb WHERE id=" + to_string(rand_line[i]);
    //    conn.query(query);
    //    while (conn.next()) {
    //        lines.push_back(Line(stoi(conn.value(0)), stoi(conn.value(1)), stoi(conn.value(2)), stoi(conn.value(3))));
    //    }
    //}
    //const int polygon_size = 0;
    //int rand_polygon[polygon_size];
    //srand(time(NULL));
    //for (int i = 0; i < polygon_size; i++) {
    //    rand_polygon[i] = rand() % 1562 + 1; // Generate a random number between 1 and 1562
    //}
    //for (int i = 0; i < polygon_size; ++i) {
    //    string query = "SELECT doxs FROM polygon WHERE id=" + to_string(rand_polygon[i]);
    //    conn.query(query);
    //    while (conn.next()) {
    //        stringstream ss(conn.value(0));
    //        vector<int> nums;
    //        vector<Point> points3;
    //        int num;
    //        while (ss >> num) {
    //            nums.push_back(num);
    //            if (ss.peek() == ',') {
    //                ss.ignore();
    //            }
    //        }
    //        for (int i = 0; i < nums.size(); i+=2) {
    //            points3.push_back(Point(nums[i], nums[i + 1]));
    //        }
    //        polygons.push_back(polygon(points3));
    //    }
    //}
    /*for (int i = 0; i < point_size; ++i) {
        cout <<"x:"<< points[i].x <<"y:"<< points[i].y <<"type:"<< points[i].type << endl;
    }*/
   /* for (int i = 0; i < line_size; ++i) {
        cout << "x_first:" << lines[i].first_x << "y_first:" << lines[i].first_y << "x_end:" << lines[i].end_x <<"y_end:" << lines[i].end_y<< endl;
    }
    for (int i = 0; i < polygon_size; ++i) {
        cout << "points:";
        for (int j = 0; j < polygons[i].points.size(); ++j) {
            cout << "(" << polygons[i].points[j].x << "," << polygons[i].points[j].y << ")" << " ";
        }
        cout << endl;
    }*/
    //steady_clock::time_point begin = steady_clock::now();
    //class search search(points, lines, polygons);
    ///*class search search(points);*/
    //int maxcount = 0;
    //for (auto i = search.Result.begin(); i != search.Result.end(); ++i) {
    //    maxcount = 0;
    //    for (auto j = i->begin(); j != i->end(); ++j) {
    //        for (auto k = j->begin(); k != j->end(); ++k) {
    //            
    //        }
    //    }
    //}
    //steady_clock::time_point end = steady_clock::now();
    //auto length = end - begin;
    //cout << "耗时:" << length.count() / 1000000 << "毫秒" << endl;
    return 0;
}




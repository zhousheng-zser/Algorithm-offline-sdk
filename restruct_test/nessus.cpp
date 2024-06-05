#include <json.h>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <chrono>
#include <ctime>
#include <parser_c.hpp>
#include <fstream>
#include <algorithm> 
void smoke_test() {
    Json::FastWriter writer;
    Json::Reader reader(Json::Features::strictMode());
    Json::Value loadPluginJs;
    auto init_result =
        parser_init_plugin("/root/Glasssix_CV_SDK_beta-restruct/configure_file/plugin_configure.json", "license");
    printf("%s", init_result);
    reader.parse(std::string(init_result), loadPluginJs);
    std::cout << "loadPluginJs\n" << loadPluginJs << std::endl;
    parser_free(init_result);

    Json::Value new_param;
    new_param["models_directory"] = R"(../safemodels)";
    new_param["device"]           = Json::Int(-1);

    auto new_result = parser_create_instance("g6.smoke.detect_code", writer.write(new_param).c_str());
    Json::Value new_result_js;
    reader.parse(std::string(new_result), new_result_js);
    std::cout << "new_result_js\n" << new_result_js << std::endl;
    parser_free(new_result);

    cv::Mat img = cv::imread("../smoke/smoke2.jpg");
    Json::Value exe_param, exe_rst_js;
    exe_param["algo_params"]["dyparams"]["smoke_conf_thres"] = Json::Value(0.2);
    exe_param["algo_params"]["dyparams"]["smoke_iou_thres"]  = Json::Value(0.5);
    exe_param["data_params"]["height"]                       = Json::Int(img.rows);
    exe_param["data_params"]["width"]                        = Json::Int(img.cols);

    std::string json_str = R"(
        [
            {
                "key_points" : [
                    {"point_score" : 0.91670811176300049, "x" : 824, "y" : 216},
                    {"point_score" : 0.43254271149635315, "x" : 821, "y" : 209},
                    {"point_score" : 0.94345188140869141, "x" : 814, "y" : 212},
                    {"point_score" : 0.060975179076194763, "x" : 808, "y" : 213},
                    {"point_score" : 0.91117966175079346, "x" : 784, "y" : 222},
                    {"point_score" : 0.9437636137008667, "x" : 818, "y" : 261},
                    {"point_score" : 0.99655699729919434, "x" : 752, "y" : 278},
                    {"point_score" : 0.74054980278015137, "x" : 829, "y" : 320},
                    {"point_score" : 0.9943581223487854, "x" : 726, "y" : 344},
                    {"point_score" : 0.80455952882766724, "x" : 843, "y" : 375},
                    {"point_score" : 0.99040353298187256, "x" : 757, "y" : 362},
                    {"point_score" : 0.9942474365234375, "x" : 820, "y" : 389},
                    {"point_score" : 0.99852776527404785, "x" : 776, "y" : 404},
                    {"point_score" : 0.99325501918792725, "x" : 844, "y" : 456},
                    {"point_score" : 0.99803537130355835, "x" : 779, "y" : 479},
                    {"point_score" : 0.99006360769271851, "x" : 855, "y" : 529},
                    {"point_score" : 0.99535441398620605, "x" : 787, "y" : 558}
                ],
                "location" : {"x1" : 698, "x2" : 915, "y1" : 166, "y2" : 610},
                "score" : 0.89805346727371216
            },
            {
                "key_points" : [
                    {"point_score" : 0.97958976030349731, "x" : 1124, "y" : 557},
                    {"point_score" : 0.61404693126678467, "x" : 1127, "y" : 546},
                    {"point_score" : 0.99051427841186523, "x" : 1114, "y" : 550},
                    {"point_score" : 0.051749542355537415, "x" : 1115, "y" : 545},
                    {"point_score" : 0.98340684175491333, "x" : 1077, "y" : 556},
                    {"point_score" : 0.97496461868286133, "x" : 1084, "y" : 576},
                    {"point_score" : 0.99890983104705811, "x" : 1071, "y" : 625},
                    {"point_score" : 0.81537950038909912, "x" : 1125, "y" : 620},
                    {"point_score" : 0.99794930219650269, "x" : 1125, "y" : 698},
                    {"point_score" : 0.86373674869537354, "x" : 1135, "y" : 615},
                    {"point_score" : 0.99597710371017456, "x" : 1129, "y" : 620},
                    {"point_score" : 0.98421543836593628, "x" : 1137, "y" : 701},
                    {"point_score" : 0.99635004997253418, "x" : 1125, "y" : 741},
                    {"point_score" : 0.95743727684020996, "x" : 1242, "y" : 696},
                    {"point_score" : 0.99083894491195679, "x" : 1226, "y" : 764},
                    {"point_score" : 0.90174776315689087, "x" : 1177, "y" : 765},
                    {"point_score" : 0.9610980749130249, "x" : 1165, "y" : 842}
                ],
                "location" : {"x1" : 1017, "x2" : 1271, "y1" : 496, "y2" : 879},
                "score" : 0.85860008001327515
            },
            {
                "key_points" : [
                    {"point_score" : 0.53025168180465698, "x" : 1313, "y" : 386},
                    {"point_score" : 0.099645301699638367, "x" : 1310, "y" : 377},
                    {"point_score" : 0.62817937135696411, "x" : 1311, "y" : 380},
                    {"point_score" : 0.10320506244897842, "x" : 1280, "y" : 356},
                    {"point_score" : 0.88018053770065308, "x" : 1292, "y" : 369},
                    {"point_score" : 0.88403928279876709, "x" : 1253, "y" : 359},
                    {"point_score" : 0.99181210994720459, "x" : 1268, "y" : 383},
                    {"point_score" : 0.48002159595489502, "x" : 1293, "y" : 394},
                    {"point_score" : 0.97931456565856934, "x" : 1323, "y" : 429},
                    {"point_score" : 0.39280253648757935, "x" : 1315, "y" : 380},
                    {"point_score" : 0.91964256763458252, "x" : 1323, "y" : 385},
                    {"point_score" : 0.92331618070602417, "x" : 1176, "y" : 438},
                    {"point_score" : 0.97702264785766602, "x" : 1185, "y" : 452},
                    {"point_score" : 0.75993871688842773, "x" : 1255, "y" : 485},
                    {"point_score" : 0.92093205451965332, "x" : 1257, "y" : 503},
                    {"point_score" : 0.56061351299285889, "x" : 1278, "y" : 560},
                    {"point_score" : 0.74853616952896118, "x" : 1280, "y" : 577}
                ],
                "location" : {"x1" : 1140, "x2" : 1356, "y1" : 313, "y2" : 596},
                "score" : 0.83788543939590454
            }
        ]
    )";


    Json::Value jsonobj_detect_resulttemp;
    reader.parse(json_str, jsonobj_detect_resulttemp);

    exe_param["algo_params"]["dyparams"]["info_list"] = jsonobj_detect_resulttemp;

    auto execute_result = parser_execute(new_result_js["instance_id"].asString().c_str(),
        writer.write(exe_param).c_str(), reinterpret_cast<char*>(img.data), img.step[0] * img.rows, nullptr, 0);

    reader.parse(std::string(execute_result), exe_rst_js);
    std::cout << "exe_rst_js\n" << execute_result << std::endl;
    // parser_free(execute_result);

    Json::Value jsonobj_detect_result;
    reader.parse(execute_result, jsonobj_detect_result);

    std::cout << "toStyledString: " << jsonobj_detect_result.toStyledString();
    // std::cout<<"to string: "<<exe_rst_js.to_st


    //reader.parse(result, jsonobj_detect_result);
    //std::cout << "result: " << result << std::endl;

    std::cout << "toStyledString: " << jsonobj_detect_result.toStyledString();

    parser_release_instance(new_result_js["instance_id"].asString().c_str());
}

void climb_test() {
    Json::FastWriter writer;
    Json::Reader reader(Json::Features::strictMode());
    Json::Value loadPluginJs;
    char* init_result =
        parser_init_plugin("/root/Glasssix_CV_SDK_beta-restruct/configure_file/plugin_configure.json", "license");
    printf("%s", init_result);

    
    Json::Value new_param;
    new_param["models_directory"] = "/root/Glasssix_CV_SDK_beta-restruct/models/rk3588";
    new_param["device"]           = Json::Int(-1);

    char* new_result = parser_create_instance("g6.climb.detect_code", writer.write(new_param).c_str());
    printf("%s", new_result);
    Json::Value new_result_js;
    reader.parse(std::string(new_result), new_result_js);

    cv::Mat img = cv::imread("/root/img/climb.jpg");
    Json::Value exe_param, exe_rst_js;
    exe_param["algo_params"]["dyparams"]["conf_thres"] = Json::Value(0.5);
    exe_param["algo_params"]["dyparams"]["nms_thres"]  = Json::Value(0.5);
    exe_param["data_params"]["height"]                       = Json::Int(img.rows);
    exe_param["data_params"]["width"]                        = Json::Int(img.cols);
    char* execute_result = parser_execute(new_result_js["instance_id"].asString().c_str(),
        writer.write(exe_param).c_str(), reinterpret_cast<char*>(img.data), img.step[0] * img.rows, nullptr, 0);
    printf("%s", execute_result);

}
void pump_work_status_test() {
    Json::FastWriter writer;
    Json::Reader reader(Json::Features::strictMode());
    Json::Value loadPluginJs;
    char* init_result =
        parser_init_plugin("/root/Glasssix_CV_SDK_beta-restruct/configure_file/plugin_configure.json", "license");
    printf("%s", init_result);


    Json::Value new_param;
    new_param["models_directory"] = "/root/Glasssix_CV_SDK_beta-restruct/models/rk3588";
    new_param["device"]           = Json::Int(-1);

    char* new_result = parser_create_instance("g6.pump_work_status.work_status", writer.write(new_param).c_str());
    printf("%s", new_result);
    Json::Value new_result_js;
    reader.parse(std::string(new_result), new_result_js);

    cv::Mat img = cv::imread("/root/img/pump_work_status.jpg");
    Json::Value exe_param, exe_rst_js;
    Json::Value jarray_mask_roi(Json::arrayValue);
    jarray_mask_roi.append(741);
    jarray_mask_roi.append(412);
    jarray_mask_roi.append(1035);
    jarray_mask_roi.append(412);
    jarray_mask_roi.append(1475);
    jarray_mask_roi.append(1080);
    jarray_mask_roi.append(847);
    jarray_mask_roi.append(1080);
    exe_param["algo_params"]["dyparams"]["big_paint_room"] = Json::Value(1);
    exe_param["algo_params"]["dyparams"]["mask_roi"]       = jarray_mask_roi;
    exe_param["data_params"]["height"]                 = Json::Int(img.rows);
    exe_param["data_params"]["width"]                  = Json::Int(img.cols);
    char* execute_result                               = parser_execute(new_result_js["instance_id"].asString().c_str(),
                                      writer.write(exe_param).c_str(), reinterpret_cast<char*>(img.data), img.step[0] * img.rows, nullptr, 0);
    printf("%s", execute_result);
}


void pump_mask_test() {
    Json::FastWriter writer;
    Json::Reader reader(Json::Features::strictMode());
    Json::Value loadPluginJs;
    char* init_result =
        parser_init_plugin("/root/Glasssix_CV_SDK_beta-restruct/configure_file/plugin_configure.json", "license");
    printf("%s", init_result);


    Json::Value new_param;
    new_param["models_directory"] = "/root/Glasssix_CV_SDK_beta-restruct/models/rk3588";
    new_param["device"]           = Json::Int(-1);

    char* new_result = parser_create_instance("g6.pump_mask.detect_code", writer.write(new_param).c_str());
    printf("%s", new_result);
    Json::Value new_result_js;
    reader.parse(std::string(new_result), new_result_js);

    cv::Mat img = cv::imread("/root/img/pump_mak.jpg");
    Json::Value exe_param, exe_rst_js;
    exe_param["algo_params"]["dyparams"]["conf_thres"] = Json::Value(0.6);
    exe_param["algo_params"]["dyparams"]["nms_thres"]      = Json::Value(0.45);
    exe_param["data_params"]["height"]                     = Json::Int(img.rows);
    exe_param["data_params"]["width"]                      = Json::Int(img.cols);
    char* execute_result = parser_execute(new_result_js["instance_id"].asString().c_str(),
        writer.write(exe_param).c_str(), reinterpret_cast<char*>(img.data), img.step[0] * img.rows, nullptr, 0);
    printf("%s", execute_result);
}

void pump_pumptop_person_test() {
    Json::FastWriter writer;
    Json::Reader reader(Json::Features::strictMode());
    Json::Value loadPluginJs;
    char* init_result =
        parser_init_plugin("/root/Glasssix_CV_SDK_beta-restruct/configure_file/plugin_configure.json", "license");
    printf("%s", init_result);


    Json::Value new_param;
    new_param["models_directory"] = "/root/Glasssix_CV_SDK_beta-restruct/models/rk3588";
    new_param["device"]           = Json::Int(-1);

    char* new_result = parser_create_instance("g6.pump_pumptop_person.detect_code", writer.write(new_param).c_str());
    printf("%s", new_result);
    Json::Value new_result_js;
    reader.parse(std::string(new_result), new_result_js);

    cv::Mat img = cv::imread("/root/img/pump_pumptop_person.jpg");
    Json::Value exe_param, exe_rst_js;
    std::string json_str = R"( [{"score": 0.8786270022392273,"x1": 1027,"x2": 1151,"y1": 225,"y2": 470}])";
    Json::Value jsonobj_detect_resulttemp;
    reader.parse(json_str, jsonobj_detect_resulttemp);
    exe_param["algo_params"]["dyparams"]["person_list"] = jsonobj_detect_resulttemp;
    exe_param["algo_params"]["dyparams"]["person_area_ratio_thres"] = Json::Value(0.4);
    exe_param["data_params"]["height"]                 = Json::Int(img.rows);
    exe_param["data_params"]["width"]                  = Json::Int(img.cols);
    char* execute_result                               = parser_execute(new_result_js["instance_id"].asString().c_str(),
                                      writer.write(exe_param).c_str(), reinterpret_cast<char*>(img.data), img.step[0] * img.rows, nullptr, 0);
    printf("%s", execute_result);
}

void playphone_test() {
    Json::FastWriter writer;
    Json::Reader reader(Json::Features::strictMode());
    Json::Value loadPluginJs;
    char* init_result =
        parser_init_plugin("/root/Glasssix_CV_SDK_beta-restruct/configure_file/plugin_configure.json", "license");
    printf("%s", init_result);


    Json::Value new_param;
    new_param["models_directory"] = "/root/Glasssix_CV_SDK_beta-restruct/models/rk3588";
    new_param["device"]           = Json::Int(-1);

    char* new_result = parser_create_instance("g6.playphone.detect_code", writer.write(new_param).c_str());
    printf("%s", new_result);
    Json::Value new_result_js;
    reader.parse(std::string(new_result), new_result_js);

    cv::Mat img = cv::imread("/root/img/wsj_13.jpg");
    Json::Value exe_param, exe_rst_js;
    std::string json_str = R"( 
    [{"key_points":[{"point_score":0.9899863600730896,"x":1188,"y":524},{"point_score":0.9733928442001343,"x":1199,"y":508},{"point_score":0.9617499113082886,"x":1176,"y":512},{"point_score":0.8065480589866638,"x":1220,"y":493},{"point_score":0.7007924318313599,"x":1158,"y":502},{"point_score":0.9972207546234131,"x":1260,"y":537},{"point_score":0.9959771037101746,"x":1141,"y":545},{"point_score":0.9845753908157349,"x":1277,"y":639},{"point_score":0.9671630263328552,"x":1123,"y":646},{"point_score":0.9773275852203369,"x":1219,"y":631},{"point_score":0.95743727684021,"x":1150,"y":632},{"point_score":0.9955142140388489,"x":1240,"y":681},{"point_score":0.9942920207977295,"x":1175,"y":679},{"point_score":0.9937829375267029,"x":1196,"y":686},{"point_score":0.9902538657188416,"x":1177,"y":668},{"point_score":0.9833430051803589,"x":1167,"y":852},{"point_score":0.9777138829231262,"x":1232,"y":816}],"location":{"x1":1105,"x2":1311,"y1":434,"y2":913},"score":0.8704871535301208},{"key_points":[{"point_score":0.986828088760376,"x":1028,"y":521},{"point_score":0.9628831148147583,"x":1039,"y":508},{"point_score":0.967100977897644,"x":1016,"y":511},{"point_score":0.7108290791511536,"x":1056,"y":502},{"point_score":0.8125700354576111,"x":995,"y":507},{"point_score":0.9967142343521118,"x":1088,"y":552},{"point_score":0.9934101700782776,"x":967,"y":557},{"point_score":0.9802431464195251,"x":1111,"y":640},{"point_score":0.9452984929084778,"x":960,"y":646},{"point_score":0.9645224213600159,"x":1076,"y":612},{"point_score":0.9264369606971741,"x":993,"y":621},{"point_score":0.9928231239318848,"x":1080,"y":672},{"point_score":0.9894702434539795,"x":1005,"y":674},{"point_score":0.9870794415473938,"x":1086,"y":709},{"point_score":0.9786719083786011,"x":1006,"y":704},{"point_score":0.9624620079994202,"x":1052,"y":849},{"point_score":0.9462003111839294,"x":1018,"y":831}],"location":{"x1":950,"x2":1134,"y1":449,"y2":900},"score":0.854763388633728},{"key_points":[{"point_score":0.9816303849220276,"x":236,"y":225},{"point_score":0.9226218461990356,"x":267,"y":203},{"point_score":0.9575167298316956,"x":211,"y":180},{"point_score":0.15765491127967834,"x":278,"y":200},{"point_score":0.5782696008682251,"x":131,"y":145},{"point_score":0.9735442399978638,"x":276,"y":333},{"point_score":0.8381505608558655,"x":27,"y":282},{"point_score":0.9640516638755798,"x":327,"y":560},{"point_score":0.632729709148407,"x":0,"y":530},{"point_score":0.9683213829994202,"x":276,"y":490},{"point_score":0.8174288272857666,"x":125,"y":483},{"point_score":0.9689150452613831,"x":208,"y":755},{"point_score":0.9071478247642517,"x":52,"y":738},{"point_score":0.8832359910011292,"x":171,"y":1079},{"point_score":0.7032438516616821,"x":77,"y":1078},{"point_score":0.3838144838809967,"x":68,"y":1259},{"point_score":0.20386600494384766,"x":45,"y":1297}],"location":{"x1":0,"x2":432,"y1":13,"y2":1346},"score":0.8350804448127747},{"key_points":[{"point_score":0.957912266254425,"x":654,"y":567},{"point_score":0.20833994448184967,"x":664,"y":548},{"point_score":0.9866748452186584,"x":645,"y":533},{"point_score":0.004700060468167067,"x":620,"y":533},{"point_score":0.9851576089859009,"x":572,"y":500},{"point_score":0.8782098889350891,"x":538,"y":589},{"point_score":0.994594156742096,"x":455,"y":595},{"point_score":0.5431358814239502,"x":590,"y":752},{"point_score":0.9942474365234375,"x":472,"y":825},{"point_score":0.6617043018341064,"x":655,"y":711},{"point_score":0.991186797618866,"x":623,"y":731},{"point_score":0.9190633296966553,"x":533,"y":888},{"point_score":0.9785493016242981,"x":475,"y":920},{"point_score":0.9515940546989441,"x":835,"y":898},{"point_score":0.9905142784118652,"x":761,"y":943},{"point_score":0.9216402173042297,"x":814,"y":1183},{"point_score":0.9709643721580505,"x":752,"y":1251}],"location":{"x1":299,"x2":1021,"y1":352,"y2":1338},"score":0.7866228222846985},{"key_points":[{"point_score":0.9835337996482849,"x":859,"y":435},{"point_score":0.9783847332000732,"x":870,"y":417},{"point_score":0.9264369606971741,"x":846,"y":420},{"point_score":0.8918110132217407,"x":897,"y":404},{"point_score":0.4695962369441986,"x":834,"y":412},{"point_score":0.9923341274261475,"x":936,"y":455},{"point_score":0.9862046241760254,"x":825,"y":463},{"point_score":0.963711678981781,"x":955,"y":544},{"point_score":0.8966140151023865,"x":797,"y":555},{"point_score":0.948441743850708,"x":901,"y":490},{"point_score":0.8778960704803467,"x":817,"y":545},{"point_score":0.9742884635925293,"x":928,"y":613},{"point_score":0.9641192555427551,"x":858,"y":616},{"point_score":0.8731066584587097,"x":921,"y":667},{"point_score":0.813164234161377,"x":865,"y":667},{"point_score":0.5937860012054443,"x":946,"y":764},{"point_score":0.5216691493988037,"x":921,"y":762}],"location":{"x1":773,"x2":993,"y1":337,"y2":736},"score":0.7509182095527649},{"key_points":[{"point_score":0.9845160245895386,"x":1355,"y":527},{"point_score":0.9668514132499695,"x":1368,"y":516},{"point_score":0.9515940546989441,"x":1343,"y":515},{"point_score":0.7927852869033813,"x":1387,"y":517},{"point_score":0.7035494446754456,"x":1325,"y":512},{"point_score":0.994401752948761,"x":1405,"y":562},{"point_score":0.9884026646614075,"x":1304,"y":558},{"point_score":0.9641867876052856,"x":1426,"y":634},{"point_score":0.9008791446685791,"x":1288,"y":634},{"point_score":0.9405717849731445,"x":1390,"y":595},{"point_score":0.8734309077262878,"x":1328,"y":617},{"point_score":0.975296139717102,"x":1378,"y":684},{"point_score":0.9643886089324951,"x":1319,"y":684},{"point_score":0.9549844264984131,"x":1387,"y":642},{"point_score":0.9329437017440796,"x":1349,"y":649},{"point_score":0.8944211602210999,"x":1342,"y":801},{"point_score":0.8601343035697937,"x":1355,"y":816}],"location":{"x1":1275,"x2":1443,"y1":444,"y2":891},"score":0.7280721068382263},{"key_points":[{"point_score":0.9885804057121277,"x":1498,"y":488},{"point_score":0.9581479430198669,"x":1509,"y":476},{"point_score":0.9725714921951294,"x":1486,"y":477},{"point_score":0.6635599136352539,"x":1527,"y":482},{"point_score":0.7727022171020508,"x":1469,"y":485},{"point_score":0.9877113699913025,"x":1559,"y":540},{"point_score":0.9957518577575684,"x":1452,"y":544},{"point_score":0.9175984263420105,"x":1599,"y":615},{"point_score":0.9781354665756226,"x":1440,"y":622},{"point_score":0.9087799787521362,"x":1568,"y":552},{"point_score":0.9651191234588623,"x":1478,"y":562},{"point_score":0.9687971472740173,"x":1542,"y":665},{"point_score":0.9801293015480042,"x":1480,"y":665},{"point_score":0.920074462890625,"x":1532,"y":699},{"point_score":0.9447912573814392,"x":1494,"y":696},{"point_score":0.7799928784370422,"x":1530,"y":827},{"point_score":0.8272706270217896,"x":1533,"y":822}],"location":{"x1":1405,"x2":1621,"y1":426,"y2":878},"score":0.6519090533256531}]     
)";
    Json::Value jsonobj_detect_resulttemp;
    reader.parse(json_str, jsonobj_detect_resulttemp);
    exe_param["algo_params"]["dyparams"]["posture_info_list"] = jsonobj_detect_resulttemp;
    exe_param["algo_params"]["dyparams"]["head_conf_thres"] = Json::Value(0.6);
    exe_param["algo_params"]["dyparams"]["head_nms_thres"]  = Json::Value(0.8);
    exe_param["algo_params"]["dyparams"]["phone_conf_thres"] = Json::Value(0.7);
    exe_param["algo_params"]["dyparams"]["phone_nms_thres"]  = Json::Value(0.5);

    exe_param["data_params"]["height"]                              = Json::Int(img.rows);
    exe_param["data_params"]["width"]                               = Json::Int(img.cols);
    char* execute_result = parser_execute(new_result_js["instance_id"].asString().c_str(),
        writer.write(exe_param).c_str(), reinterpret_cast<char*>(img.data), img.step[0] * img.rows, nullptr, 0);
    printf("%s", execute_result);
}


void onphone_post_test() {
    Json::FastWriter writer;
    Json::Reader reader(Json::Features::strictMode());
    Json::Value loadPluginJs;
    char* init_result =
        parser_init_plugin("/root/Glasssix_CV_SDK_beta-restruct/configure_file/plugin_configure.json", "license");
    printf("%s", init_result);


    Json::Value new_param;
    new_param["models_directory"] = "/root/Glasssix_CV_SDK_beta-restruct/models/rk3588";
    new_param["device"]           = Json::Int(-1);

    char* new_result = parser_create_instance("g6.onphone.detect_code", writer.write(new_param).c_str());
    printf("%s", new_result);
    Json::Value new_result_js;
    reader.parse(std::string(new_result), new_result_js);

    cv::Mat img = cv::imread("/root/img/onphone.png");
    Json::Value exe_param, exe_rst_js;
    std::string json_str = R"( 
    [{"key_points":[{"point_score":0.9990226030349731,"x":443,"y":232},{"point_score":0.9984452128410339,"x":474,"y":211},{"point_score":0.991186797618866,"x":430,"y":199},{"point_score":0.9658995866775513,"x":520,"y":216},{"point_score":0.4757879674434662,"x":409,"y":188},{"point_score":0.9976859092712402,"x":553,"y":355},{"point_score":0.995685338973999,"x":366,"y":304},{"point_score":0.9738444089889526,"x":572,"y":540},{"point_score":0.9470881819725037,"x":343,"y":486},{"point_score":0.9751071333885193,"x":503,"y":417},{"point_score":0.9089417457580566,"x":345,"y":611},{"point_score":0.9596109390258789,"x":504,"y":662},{"point_score":0.9449946880340576,"x":382,"y":637},{"point_score":0.12294380366802216,"x":488,"y":766},{"point_score":0.08434179425239563,"x":361,"y":766},{"point_score":0.00431468803435564,"x":499,"y":766},{"point_score":0.0032350558321923018,"x":417,"y":766}],"location":{"x1":296,"x2":640,"y1":70,"y2":762},"score":0.8597815036773682}]
)";
    Json::Value jsonobj_detect_resulttemp;
    reader.parse(json_str, jsonobj_detect_resulttemp);
    exe_param["algo_params"]["dyparams"]["posture_info_list"] = jsonobj_detect_resulttemp;
    exe_param["algo_params"]["dyparams"]["conf_thres"]   = Json::Value(0.5);
    exe_param["algo_params"]["dyparams"]["nms_thres"] = Json::Value(0.45);
    exe_param["algo_params"]["dyparams"]["phone_distance_thres"] = Json::Value(1.0);
    exe_param["data_params"]["height"] = Json::Int(img.rows);
    exe_param["data_params"]["width"]                            = Json::Int(img.cols);
    exe_param["algo_params"]["command"]                               = Json::Value(1);
    char* execute_result               = parser_execute(new_result_js["instance_id"].asString().c_str(),
                      writer.write(exe_param).c_str(), reinterpret_cast<char*>(img.data), img.step[0] * img.rows, nullptr, 0);
    printf("%s", execute_result);
}


void onphone_head_test() {
    Json::FastWriter writer;
    Json::Reader reader(Json::Features::strictMode());
    Json::Value loadPluginJs;
    char* init_result =
        parser_init_plugin("/root/Glasssix_CV_SDK_beta-restruct/configure_file/plugin_configure.json", "license");
    printf("%s", init_result);


    Json::Value new_param;
    new_param["models_directory"] = "/root/Glasssix_CV_SDK_beta-restruct/models/rk3588";
    new_param["device"]           = Json::Int(-1);

    char* new_result = parser_create_instance("g6.onphone.detect_code", writer.write(new_param).c_str());
    printf("%s", new_result);
    Json::Value new_result_js;
    reader.parse(std::string(new_result), new_result_js);

    cv::Mat img = cv::imread("/root/img/onphone.png");
    Json::Value exe_param, exe_rst_js;
    std::string json_str = R"( 
    [{"score":0.8949732184410095,"x1":400,"x2":550,"y1":74,"y2":305}]
)";
    Json::Value jsonobj_detect_resulttemp;
    reader.parse(json_str, jsonobj_detect_resulttemp);
    exe_param["algo_params"]["dyparams"]["head_info_list"]    = jsonobj_detect_resulttemp;
    exe_param["algo_params"]["dyparams"]["conf_thres"]           = Json::Value(0.5);
    exe_param["algo_params"]["dyparams"]["nms_thres"]            = Json::Value(0.45);
    exe_param["algo_params"]["dyparams"]["phone_distance_thres"] = Json::Value(1.0);
    exe_param["data_params"]["height"]                           = Json::Int(img.rows);
    exe_param["data_params"]["width"]                            = Json::Int(img.cols);
    exe_param["algo_params"]["command"]                          = Json::Value(0);
    char* execute_result = parser_execute(new_result_js["instance_id"].asString().c_str(),
        writer.write(exe_param).c_str(), reinterpret_cast<char*>(img.data), img.step[0] * img.rows, nullptr, 0);
    printf("%s", execute_result);
}


int main()
{
    //climb_test();
    //playphone_test(); 
    onphone_post_test(); 
    onphone_head_test();
    //pump_pumptop_person_test();
    //pump_mask_test(); 
    //pump_work_status_test();
    //    smoke_test(); 
}
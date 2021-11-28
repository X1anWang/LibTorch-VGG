#include "dataSet.h"

// Traverse all .jpg pictures in the folder
void load_data_from_folder(std::string path, std::string type, std::vector<std::string> &list_images, std::vector<int> &list_labels, int label) {
    long long hFile = 0;
    struct _finddata_t fileInfo;
    std::string pathName;
    if ((hFile = _findfirst(pathName.assign(path).append("/*.*").c_str(), &fileInfo)) == -1) {
        return;
        }
    do {
        const char* s = fileInfo.name;
        const char* t = type.data();
        
        // Sub-filefolder: True
        if (fileInfo.attrib&_A_SUBDIR) {
            // Traverse all files in this sub-filefolder 
            if (strcmp(s, ".") == 0 || strcmp(s, "..") == 0) continue;
            std::string sub_path = path + "/" + fileInfo.name;
            label++;
            load_data_from_folder(sub_path, type, list_images, list_labels, label);
            }
        // If it is .type file or not
        else {
            if (strstr(s, t)) {
                std::string image_path = path + "/" + fileInfo.name;
                list_images.push_back(image_path);
                list_labels.push_back(label);
            }
        }
    } while (_findnext(hFile, &fileInfo) == 0);
    return;
}
//???
//int batch_size = 2;
//std::string image_dir = "hymenoptera_data\\train";
//auto mdataset = myDataset(image_dir, ".jpg").map(torch::data::transforms::Stack<>());
//auto mdataloader = torch::data::make_data_loader<torch::data::samplers::RandomSampler>(std::move(mdataset), batch_size);
//for (auto &batch: *mdataloader) {
//    auto data = batch.data;
//    auto target = batch.target;
//    std::cout << data.sizes() << target;
//}
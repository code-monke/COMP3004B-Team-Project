#include "constants.h"
#include "data.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

Data::Data(int cohLvl)
{
//    this->hcData = {
//        {
//            80.0, 80.0, 82.97, 87.91, 89.79, 91.59, 91.29, 94.88, 92.35, 95.67,
//            95.83, 98.82, 98.64, 101.27, 100.71, 100.95, 101.99, 98.83, 97.48, 99.93,
//            97.19, 99.26, 95.17, 95.91, 95.51, 90.97, 92.31, 86.55, 85.7, 83.78,
//            82.82, 78.83, 77.83, 76.85, 73.89, 71.98, 71.15, 69.4, 68.76, 66.24,
//            65.86, 61.63, 62.57, 60.68, 60.97, 60.45, 59.13, 60.0, 59.08, 61.35,
//            58.82, 59.48, 60.33, 63.35, 62.54, 64.89, 67.37, 67.99, 72.71, 73.52,
//            73.41, 77.36, 78.34, 79.34, 83.33, 82.3, 88.23, 88.1, 87.88, 92.57,
//            92.14, 95.58, 95.87, 98.01, 95.97, 99.76, 100.36, 98.76, 99.97, 99.98,
//            97.79, 99.4, 97.81, 96.04, 97.09, 95.97, 92.69, 95.26, 93.7, 88.02,
//            86.24, 86.38, 85.46, 84.49, 79.5, 77.5, 78.51, 76.56, 72.67, 68.85,
//            71.12, 68.5, 67.0, 66.65, 65.44, 64.41, 60.54, 58.87, 60.38, 62.09,
//            62.0, 59.11, 61.42, 60.92, 62.61, 64.49, 61.54, 63.76, 64.13, 66.64,
//            69.27, 73.01, 70.84, 74.74, 75.69, 78.67, 80.67, 81.66, 85.63, 88.55,
//            90.4, 89.17, 90.84, 93.39, 94.81, 94.08, 98.18, 96.12, 98.87, 97.44,
//            97.81, 100.99, 97.96, 100.74, 97.31, 99.7, 97.9, 98.91, 93.77, 95.46,
//            92.01, 89.42, 88.73, 86.93, 86.06, 82.13, 82.16, 82.16, 79.16, 76.18,
//            74.24, 74.36, 72.55, 68.84, 67.24, 65.76, 62.43, 63.26, 63.25, 59.42,
//            59.77, 58.32, 58.06, 61.0, 58.15, 61.49, 59.02, 60.75, 64.66, 61.74,
//            66.98, 67.37, 65.9, 70.55, 69.31, 72.15, 77.06, 79.02, 79.01, 80.01,
//            81.0, 83.96, 86.87, 90.71, 91.46, 93.11, 95.64, 95.03, 96.27, 97.35
//        },
//        {
//            13.0, 10.0, 10.0, 12.4, 12.4, 11.2, 10.0, 6.4, 7.6, 10.0,
//            12.4, 10.0, 10.0, 11.2, 10.0, 8.8, 7.6, 16.0, 10.0, 13.6,
//            13.6, 12.4, 10.0, 11.2, 10.0, 11.2, 8.8, 12.4, 12.4, 11.2,
//            11.2, 7.6, 8.8, 11.2, 13.6, 14.8, 12.4, 12.4, 10.0, 7.49
//        }
//    };

//    this->mcData = {
//        {
//            78.0, 81.0, 80.97, 83.91, 85.79, 87.59, 96.29, 89.88, 98.35, 92.67,
//            95.83, 98.82, 93.64, 98.27, 100.71, 97.95, 98.99, 98.83, 100.48, 99.93,
//            99.19, 97.26, 96.17, 89.91, 97.51, 87.97, 95.31, 89.55, 91.7, 84.78,
//            85.82, 76.83, 82.83, 73.85, 73.89, 76.98, 70.15, 73.4, 65.76, 71.24,
//            67.86, 58.63, 57.57, 60.68, 60.97, 65.45, 65.13, 58.0, 62.08, 59.35,
//            57.82, 57.48, 65.33, 67.35, 60.54, 69.89, 71.37, 66.99, 73.71, 72.52,
//            76.41, 79.36, 82.34, 85.34, 81.33, 81.3, 85.23, 83.1, 90.88, 90.57,
//            92.14, 95.58, 100.87, 101.01, 97.97, 100.76, 98.36, 97.76, 103.97, 102.98,
//            101.79, 97.4, 98.81, 95.04, 95.09, 98.97, 90.69, 93.26, 93.7, 86.02,
//            90.24, 81.38, 80.46, 78.49, 76.5, 82.5, 80.51, 79.56, 74.67, 68.85,
//            72.12, 64.5, 69.0, 67.65, 58.44, 60.41, 63.54, 56.87, 57.38, 65.09,
//            64.0, 59.11, 62.42, 61.92, 59.61, 67.49, 58.54, 66.76, 65.13, 71.64,
//            68.27, 75.01, 77.84, 71.74, 75.69, 79.67, 75.67, 78.66, 83.63, 83.55,
//            83.4, 89.17, 93.84, 90.39, 89.81, 93.08, 97.18, 94.12, 93.87, 94.44,
//            94.81, 102.99, 95.96, 94.74, 95.31, 97.7, 99.9, 92.91, 95.77, 97.46,
//            98.01, 93.42, 86.73, 92.93, 87.06, 85.13, 79.16, 83.16, 82.16, 75.18,
//            72.24, 75.36, 73.55, 71.84, 72.24, 64.76, 68.43, 63.26, 59.25, 63.42,
//            56.77, 63.32, 62.06, 60.0, 62.15, 63.49, 61.02, 58.75, 59.66, 62.74,
//            68.98, 64.37, 64.9, 71.55, 66.31, 70.15, 70.06, 73.02, 74.01, 82.01,
//            85.0, 87.96, 91.87, 87.71, 92.46, 89.11, 98.64, 91.03, 93.27, 99.35
//        },
//        {
//            2.68, 3.21, 2.68, 2.24, 2.94, 3.03, 3.21, 3.12, 3.21, 2.94,
//            3.47, 2.77, 3.21, 2.59, 2.86, 2.86, 2.68, 2.86, 3.65, 3.21,
//            3.21, 3.38, 2.77, 2.94, 3.03, 3.38, 3.03, 3.47, 3.3, 3.03,
//            2.86, 2.94, 3.12, 2.94, 2.68, 2.77, 3.12, 3.3, 3.03, 3.13
//        }
//    };

//    this->lcData = {
//        {
//            77.0, 74.0, 73.97, 82.91, 95.79, 84.59, 94.29, 82.88, 87.35, 99.67,
//            100.83, 104.82, 92.64, 93.27, 101.71, 97.95, 100.99, 102.83, 109.48, 101.93,
//            90.19, 92.26, 91.17, 96.91, 83.51, 93.97, 85.31, 85.55, 81.7, 86.78,
//            75.82, 79.83, 77.83, 69.85, 78.89, 82.98, 72.15, 74.4, 57.76, 62.24,
//            57.86, 65.63, 65.57, 58.68, 53.97, 66.45, 57.13, 50.0, 66.08, 56.35,
//            56.82, 53.48, 71.33, 53.35, 56.54, 60.89, 61.37, 59.99, 71.71, 70.52,
//            74.41, 70.36, 80.34, 74.34, 79.33, 83.3, 89.23, 91.1, 79.88, 87.57,
//            95.14, 95.58, 101.87, 102.01, 103.97, 89.76, 92.36, 92.76, 103.97, 92.98,
//            97.79, 89.4, 101.81, 97.04, 106.09, 105.97, 100.69, 86.26, 101.7, 93.02,
//            90.24, 86.38, 81.46, 87.49, 89.5, 86.5, 70.51, 77.56, 79.67, 74.85,
//            78.12, 67.5, 74.0, 70.65, 66.44, 58.41, 60.54, 56.87, 58.38, 59.09,
//            70.0, 50.11, 64.42, 59.92, 64.61, 58.49, 65.54, 72.76, 56.13, 66.64,
//            66.27, 79.01, 81.84, 77.74, 82.69, 82.67, 90.67, 90.66, 94.63, 82.55,
//            95.4, 96.17, 100.84, 92.39, 94.81, 89.08, 104.18, 107.12, 102.87, 93.44,
//            95.81, 99.99, 99.96, 102.74, 105.31, 103.7, 103.9, 97.91, 101.77, 102.46,
//            102.01, 94.42, 84.73, 89.93, 85.06, 79.13, 80.16, 82.16, 86.16, 78.18,
//            84.24, 80.36, 65.55, 63.84, 62.24, 70.76, 59.43, 72.26, 54.25, 60.42,
//            64.77, 68.32, 57.06, 56.0, 56.15, 51.49, 61.02, 59.75, 52.66, 61.74,
//            72.98, 72.37, 63.9, 67.55, 75.31, 81.15, 81.06, 79.02, 69.01, 91.01,
//            93.0, 90.96, 87.87, 80.71, 100.46, 102.11, 84.64, 88.03, 101.27, 98.35
//        },
//        {
//            1.3, 1.23, 1.1, 1.15, 1.12, 1.07, 1.1, 1.2, 1.05, 1.2,
//            1.54, 0.97, 0.97, 1.07, 1.2, 1.2, 1.36, 1.23, 1.15, 1.25,
//            1.05, 0.97, 1.07, 1.12, 1.28, 1.51, 1.1, 1.28, 0.86, 1.28,
//            0.92, 1.12, 1.23, 1.2, 1.23, 1.07, 1.12, 1.49, 1.41, 1.07
//        }
//    };

//    if (cohLvl == HIGH_COH) activeData = &this->hcData;
//    if (cohLvl == MED_COH) activeData = &this->mcData;
//    if (cohLvl == LOW_COH) activeData = &this->lcData;

    QByteArray data;
    switch (cohLvl) {
    case LOW_COH: {
        QFile file("lcData.json");
        if(file.exists() && file.open(QIODevice::ReadOnly)) {
            data = file.readAll();
            file.close();
        }
        break;
    }
    case MED_COH: {
        QFile file("mcData.json");
        if(file.exists() && file.open(QIODevice::ReadOnly)) {
            data = file.readAll();
            file.close();
        }
        break;
    }
    case HIGH_COH: {
            QFile file("hcData.json");
            if(file.exists() && file.open(QIODevice::ReadOnly)) {
                data = file.readAll();
                file.close();
            }
            break;
        }
    default:
        break;
    }

    if(data.size()>0) {
        QJsonParseError error;
        QJsonDocument jsonDoc = QJsonDocument::fromJson(data, &error);
        if(error.error != QJsonParseError::NoError) {
            throw error.errorString();
        }
        if(jsonDoc.isObject()) {
            QJsonObject obj = jsonDoc.object();
            QJsonArray heartRateArray = obj.take("heartRate").toArray();
            QJsonArray coherenceArray = obj.take("coherence").toArray();
            for(int i=0;i<heartRateArray.count();i++) {
                heartRateData.push_back(heartRateArray.at(i).toDouble());
            }
            for(int i=0;i<coherenceArray.count();i++) {
                coherenceData.push_back(coherenceArray.at(i).toDouble());
            }
        }
    }
}

double Data::getHeartRate(int t){
    if ((unsigned)t > heartRateData.size()) return -1;
    return heartRateData[t];
}

double Data::getCoherence(int t){
    if (t < 5 || (unsigned)t > coherenceData.size()) return -1;
    int index = t / 5;
    return coherenceData[index];
}




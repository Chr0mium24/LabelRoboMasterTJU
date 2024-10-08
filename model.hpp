//
// Created by xinyang on 2021/4/28.
//

#ifndef _MODEL_HPP_
#define _MODEL_HPP_

#include <opencv2/opencv.hpp>
#include <QMap>
#include <QString>
#include <QPoint>
#include <QPolygon>

struct box_t {
    QPointF pts[4];
    int color_id = 0, tag_id = 0;
    float conf = -1;

    QString getName() const {
        // static const QString tag2name[] = {"G", "1", "2", "3", "4", "5", "O", "Bs", "Bb", "3b", "4b", "5b"};
        // static const QString color2name[] = {"B", "R", "N", "P"};
        // return color2name[color_id] + tag2name[tag_id];
        switch (tag_id)
        {
            case 0:
                return "Sentry";
            case 1:
                return "1";
            case 2:
                return "2";
            case 3:
                return "3_small";
            case 4:
                return "4_small";
            case 5:
                return "5_small";
            case 6:
                return "Outpost";
            case 7:
                return "Base_small";
            case 8:
                return "Base_big";
            case 9:
                return "3_big";
            case 10:
                return "4_big";
            case 11:
                return "5_big";
            default:
                return "Unknown";
        }
    }

    bool setByName(const QString &name) {
        // static const QMap<QString, int> name2tag = {{"G", 0},
        //                                             {"1", 1},
        //                                             {"2", 2},
        //                                             {"3", 3},
        //                                             {"4", 4},
        //                                             {"5", 5},
        //                                             {"O", 6},
        //                                             {"s", 7},
        //                                             {"b", 8}};
        // static const QMap<QString, int> name2color = {{"B", 0},
        //                                               {"R", 1},
        //                                               {"N", 2},
        //                                               {"P", 3}};
        // if (name2color.contains(name[0]) && name2tag.contains(name[1])) {
        //     color_id = name2color[name[0]];
        //     tag_id = name2tag[name[1]];
        //     return true;
        // } else {
        //     return false;
        // }
        if (name == "Sentry") {
            tag_id = 0;
            return true;
        } 
        else if (name == "1") {
            tag_id = 1;
            return true;
        }
        else if (name == "2") {
            tag_id = 2;
            return true;
        }
        else if (name == "3_small") {
            tag_id = 3;
            return true;
        }
        else if (name == "4_small") {
            tag_id = 4;
            return true;
        }
        else if (name == "5_small") {
            tag_id = 5;
            return true;
        }
        else if (name == "Outpost") {
            tag_id = 6;
            return true;
        }
        else if (name == "Base_small") {
            tag_id = 7;
            return true;
        }
        else if (name == "Base_big") {
            tag_id = 8;
            return true;
        }
        else if (name == "3_big") {
            tag_id = 9;
            return true;
        }
        else if (name == "4_big") {
            tag_id = 10;
            return true;
        }
        else if (name == "5_big") {
            tag_id = 11;
            return true;
        }
        else {
            return false;
        }
    }

    QPolygonF getStandardPloygon() const {
        QPolygonF pts;
        pts.append({0., 0.});
        pts.append({0., (2 <= tag_id && tag_id <= 7) ? (725.) : (660.)});
        pts.append({(2 <= tag_id && tag_id <= 7) ? (780.) : (1180.), (2 <= tag_id && tag_id <= 7) ? (725.) : (660.)});
        pts.append({(2 <= tag_id && tag_id <= 7) ? (780.) : (1180.), 0.});
        return pts;
    }
};

class SmartModel {
public:
    explicit SmartModel();

    bool run(const QString &image_file, QVector<box_t> &boxes);

    QString get_mode() const { return mode; }

private:
    cv::dnn::Net net;
    QString mode;
};

#endif /* _MODEL_HPP_ */

#ifndef K_LINE_WALL_SDF32DSF_
#define K_LINE_WALL_SDF32DSF_

#include <QtWidgets/QWidget>

#include "ui_klinewall.h"

#include "stockalldaysinfo.h"

class KLineWall : public QWidget
{
public:

    KLineWall();

    Ui_KLineWallForm  ui;

protected:

    void paintEvent(QPaintEvent*);

private:

    std::list<StockDayInfo>  stk_days_infos_;

    std::string stockNum;
    StockAllDaysInfo stockAllDaysInfo;  //һ֧��Ʊ��������������Ϣ
    float lowestMinPrice;
    float highestMaxPrice;

};


#endif
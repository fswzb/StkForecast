
#include "kline_wall.h"

#include "dayklinedialog.h"

#include <QPainter>


KLineWall::KLineWall() : QWidget(nullptr)
{
    ui.setupUi(this);

#if 0
    StockDayInfo std_data;
    std_data.ReadData("600816 20171116 14.30 14.25 14.42 14.09 339000000 235862");
    stk_days_infos_.push_back(std_data);
#else
    this->highestMaxPrice = stockAllDaysInfo.GetHighestMaxPrice();
    this->lowestMinPrice = stockAllDaysInfo.GetLowestMinPrice();
#endif
}

void KLineWall::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);

    auto mm_h = this->height();
    auto mm_w = this->width();
    /*
    ������(���м۸�ֵ)��((HighestMaxPrice - lowestMinPrice) * i)/7  + lowestMinPrice
    ������(����)���ֳ�60�ȷݣ�ÿ��15���أ�ÿ��ĺ�����
    j*15+1  j*15*8
    ÿ���������:���̼�:350*(���̼�-lowestMinPrice)/(HighestMaxPrice - lowestMinPrice)
    ���̼�:350*(���̼�-lowestMinPrice)/(HighestMaxPrice - lowestMinPrice)
    ��߼�:350*(��߼�-lowestMinPrice)/(HighestMaxPrice - lowestMinPrice)
    ��ͼ�:350*(���̼�-lowestMinPrice)/(HighestMaxPrice - lowestMinPrice)

    ���ο�ȣ�13����
    ���θ߶ȣ�350*(���̼�-���̼�)/(HighestMaxPrice - lowestMinPrice)����
    */

    //����ƽ��
    painter.translate(30, 400);
    //painter.translate(70,600);

    painter.drawText(-30, 0, "(0,0)");
    QPen pen; //����
    //���Ʊ�����������
    pen.setStyle(Qt::DotLine);   //���û��ʷ�� ����
    painter.setPen(pen);
    //��������
    for(int i = 0; i < 8; i++)
    {
        painter.drawLine(0, -50*i, 900, -50*i);
    }

    //    //�������� ��ʵ��Ҫ���ݵ�ǰ������ȷ�����嶨��ʲôλ�� ÿ�����Ӵ���һ����
    //    for(int i = 0; i < 4; i++)
    //    {
    //        painter.drawLine(150*i,0,150*i,-350);
    //    }
    //����K��ͼ

    std::list<StockDayInfo>::iterator iter;
    float openPrice;//���̼�
    float closePrice;//���̼�
    float maxPrice;//��߼�
    float minPrice;//��ͼ�
    float marketMoney;//�ɽ���
    int j = 0;
    //cout<<stockAllDaysInfo.GetStockAllDaysInfoList().size()<<endl;
    //������ֻ��Ҫ���60�����ݣ������ڵ���60������������ͼ
    for(iter = stockAllDaysInfo.stockAllDaysInfoList.begin();
        iter != stockAllDaysInfo.stockAllDaysInfoList.end(); 
        iter++, j++)
    {
        //��ͼÿ��Ĺ�Ʊ��Ϣ
        //((StockDayInfo)(*iter)).Display();
        //��ȡÿ��Ĺ�Ʊ���ݣ����һ֧��Ʊ����߼� ��ͼ� ���̼� ���̼�
        minPrice = ((StockDayInfo)(*iter)).GetMinPrice();
        maxPrice = ((StockDayInfo)(*iter)).GetMaxPrice();
        openPrice = ((StockDayInfo)(*iter)).GetOpenPrice();
        closePrice = ((StockDayInfo)(*iter)).GetClosePrice();
        std::cout<<minPrice<<"\t"<<maxPrice<<"\t"<<openPrice<<"\t"<<closePrice << std::endl;

         auto item_w = (mm_w / 8) ;
         int k_bar_w = item_w-2;

		 QBrush brush(QColor(255,0,0)); //��ˢ
		 pen.setStyle(Qt::SolidLine);
        //��ͼÿ��Ĺ�Ʊ��K��ͼ��
        if(openPrice <= closePrice)
        {
            pen.setColor(QColor(255,0,0));
			brush.setColor(QColor(255,0,0));
        }
        else
        { 
            pen.setColor(QColor(0,255,0)); 
			brush.setColor(QColor(0,255,0));
        }
		const auto base_val = mm_h / 2; //350 
		painter.setPen(pen); //��ӻ���
        painter.setBrush(brush); //��ӻ�ˢ
            
		auto pos_y = -1 * base_val * (openPrice-lowestMinPrice)/(highestMaxPrice - lowestMinPrice);
		auto h_1 = -1 * base_val *(closePrice - openPrice)/(highestMaxPrice - lowestMinPrice);
        painter.drawRect(j * item_w + 1,  pos_y, k_bar_w, h_1); //���ƾ���
		
        painter.drawLine(j * item_w + k_bar_w/2, -1 * base_val * (maxPrice-lowestMinPrice)/(highestMaxPrice - lowestMinPrice),
            j * item_w + k_bar_w/2, -1 * base_val * (minPrice-lowestMinPrice)/(highestMaxPrice - lowestMinPrice));   //����ֱ��

    }
}
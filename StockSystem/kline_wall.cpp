
#include "kline_wall.h"

#include "dayklinedialog.h"

#include <QPainter>
#include <qevent.h>

#include <qdebug.h>

KLineWall::KLineWall() 
    : QWidget(nullptr)
    , show_cross_line_(false)
    , is_repaint_k_(true)
    , k_num_(8)
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

    QPalette pal = this->palette();
    pal.setColor(QPalette::Background, Qt::black);
    this->setAutoFillBackground(true);
    this->setPalette(pal);

    k_cycle_tag_ = "����";
    k_cycle_year_ = 2017;
}

void KLineWall::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    qDebug() << "paintEvent QCursor::pos  x:" << QCursor::pos().x() << " y: "<< QCursor::pos().y() << "\n";
    auto pos_from_global = mapFromGlobal(QCursor::pos());
    qDebug() << "paintEvent x:" << pos_from_global.x() << " y: "<< pos_from_global.y() << "\n";
    
    const int head_h = 30;
    const int bottom1_h = 30;
    const int bottom2_h = 30;
    const int bottom_h = bottom1_h + bottom2_h;
    const int mm_h = this->height() - head_h - bottom_h;
    const int mm_w = this->width();
    const int empty_right_w = 30;
    static const int right_w = 30;
    float price_per_len = (highestMaxPrice - lowestMinPrice) / float(mm_h);
      
     /*
     ------------------------>
     |
     |
     |
     |
    \|/
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
    //painter.translate(30, 400);
     
    QPen pen; 
    pen.setColor(Qt::white);
  
    painter.translate(0, this->height() - bottom_h);
    painter.drawText(0, 0, "(0,0)");
 
    //���Ʊ�����������
    pen.setColor(Qt::red);
    painter.setPen(pen);

    // right line
    painter.drawLine(mm_w - right_w, bottom_h, mm_w - right_w, -1 * this->height());

    // bottom calender  
    painter.drawLine(0, bottom1_h, mm_w, bottom1_h);
    painter.drawLine(0, bottom_h-1, mm_w, bottom_h-1);

    painter.drawText(mm_w - right_w, bottom_h-1, QString::fromLocal8Bit(k_cycle_tag_.c_str()));
    painter.drawText(0, bottom_h-1, QString("%1").arg(k_cycle_year_));

    pen.setStyle(Qt::DotLine);   //���û��ʷ�� ����
    painter.setPen(pen);

    //��������
    const int num = 8;
    const int part_h = mm_h / num;
    for(int i = 0; i < num; i++)
    {
        int pos_y = (-1) * part_h*i;
        
        painter.drawText(mm_w - right_w, pos_y, QString("%1").arg(lowestMinPrice + (price_per_len * part_h * i) ));
        painter.drawLine(0, pos_y, mm_w-right_w, pos_y);
    }
    
    //    //�������� ��ʵ��Ҫ���ݵ�ǰ������ȷ�����嶨��ʲôλ�� ÿ�����Ӵ���һ����
    //    for(int i = 0; i < 4; i++)
    //    {
    //        painter.drawLine(150*i,0,150*i,-350);
    //    }

    //����K��ͼ -------------------------------------

    //if( is_repaint_k_ )
    {
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
        iter != stockAllDaysInfo.stockAllDaysInfoList.end() && j < k_num_; 
        iter++, j++)
    {
        //��ͼÿ��Ĺ�Ʊ��Ϣ
        //((StockDayInfo)(*iter)).Display();
        //��ȡÿ��Ĺ�Ʊ���ݣ����һ֧��Ʊ����߼� ��ͼ� ���̼� ���̼�
        minPrice = ((StockDayInfo)(*iter)).GetMinPrice();
        maxPrice = ((StockDayInfo)(*iter)).GetMaxPrice();
        openPrice = ((StockDayInfo)(*iter)).GetOpenPrice();
        closePrice = ((StockDayInfo)(*iter)).GetClosePrice();
        qDebug()<<openPrice<<"\t" << closePrice <<minPrice<<"\t"<<maxPrice<<"\t"<< "\n";

         auto item_w = ((mm_w - empty_right_w - right_w)/ k_num_) ;
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
		//const auto base_val = mm_h / 2; //350 
		painter.setPen(pen); //��ӻ���
        painter.setBrush(brush); //��ӻ�ˢ
            
		auto pos_y = -1 * mm_h * (openPrice - lowestMinPrice)/(highestMaxPrice - lowestMinPrice);
		auto h_1 = -1 * mm_h *(closePrice - openPrice)/(highestMaxPrice - lowestMinPrice);
        painter.drawRect(j * item_w + 1,  pos_y, k_bar_w, h_1); //���ƾ���
		
        painter.drawLine(j * item_w + k_bar_w/2
            , -1 * mm_h * (maxPrice-lowestMinPrice)/(highestMaxPrice - lowestMinPrice)
            , j * item_w + k_bar_w/2
            , -1 * mm_h * (minPrice-lowestMinPrice)/(highestMaxPrice - lowestMinPrice));   //����ֱ��

        if( pos_from_global.x() >= j * item_w + 1 && pos_from_global.x() <= j * item_w + 1 + k_bar_w )
            k_data_str_ = iter->transacteDate; 
      }
    }

    painter.translate(0, -1 * (this->height() - bottom_h));
    
    pen.setColor(Qt::white);
    pen.setStyle(Qt::SolidLine); 
    painter.setPen(pen);
    if( show_cross_line_ )
    {
        qDebug() << "pos y " << (float)pos_from_global.y() << "\n";
        painter.drawLine(0, pos_from_global.y(), mm_w-right_w, pos_from_global.y());
        painter.drawLine(pos_from_global.x(), head_h, pos_from_global.x(), this->height()/* - head_h*/); 
        painter.drawText( mm_w-right_w, pos_from_global.y(), QString("%1").arg(lowestMinPrice + price_per_len * (this->height() - bottom_h - pos_from_global.y()) ) );
      
      //painter.drawText( pos_from_global.x() - 30, -1 * (mm_h - pos_from_global.y()), QString("%1").arg(lowestMinPrice + (float)(mm_h - pos_from_global.y()) * price_per_len ));
    }
    painter.drawText(pos_from_global.x(), this->height()-1, k_data_str_.c_str());
    is_repaint_k_ = true;
}

void KLineWall::mouseDoubleClickEvent(QMouseEvent *e)
{
    qDebug() << " x:" << e->pos().x() <<" y:" << e->pos().y() << "\n";
    show_cross_line_ = !show_cross_line_;
    setMouseTracking(show_cross_line_);

    /*if( show_cross_line_ )
        setCursor(Qt::CrossCursor);*/
     
    update();
}

// this->mapFromGlobal(this->cursor().pos()) == event.pos()
void KLineWall::mouseMoveEvent(QMouseEvent *e)
{ 
   // qDebug() << "===================================\n";
    //// ��ͼ����ԭ��(0,0)��Ӧ�������꣨�������꣩
    //qDebug() << "view->mapToScene(0, 0):" << this->mapToScene(0, 0);

    //// ��������ԭ��(0,0)��Ӧ��ͼ���꣨��ͼ���꣩
    //qDebug() << "view->mapFromScene(0, 0):" << view->mapFromScene(0, 0);

    //// �������Ͻ����꣨�������꣩
    //QPointF p1 = QPointF(scene->sceneRect().topLeft());
    //qDebug() << "p1:" << p1;

    //// �������ϽǶ�Ӧ��ͼ���꣨��ͼ���꣩
    //qDebug() << "view->mapFromScene(p1.x(), p1.y())" << view->mapFromScene(p1.x(), p1.y());
    //qDebug() << " x:" << e->pos().x() <<" y:" << e->pos().y() << "\n";
    // 
    //qDebug() << "===================================\n";
    //QPen pen; //����
    //pen.setColor(Qt::white);
    //pen.setStyle(Qt::SolidLine); 

    /*QPainter painter(this);
    painter.translate(30, 50);
    painter.setPen(pen);
    auto mm_w = this->width();
    auto mm_h = this->height();*/
     
    auto pos = e->pos();
    //auto pos_mapped = mapToGlobal(pos);
          
    //auto pos_mapped = mapFromGlobal(e->pos());
    //auto pos_mapped = mapToParent(e->pos());
    //is_repaint_k_ = false;
    update();
    
}

void KLineWall::keyPressEvent(QKeyEvent *e)
{
    qDebug() << "key " << e->key() << "\n";
    auto key_val = e->key();
    switch( key_val )
    {
    case Qt::Key_Up:
        {
            if( k_num_ > 1 )
            {
                k_num_ --;
                update();
            }
            break;
        }
    case Qt::Key_Down:
        { 
            k_num_ ++;
            update();
            break;
        }
    default: break;
    }

    /*if( e->key() == Qt::Key_Down && k_num_ > 0 )
    {
        k_num_ --;
        update();
    }*/
}
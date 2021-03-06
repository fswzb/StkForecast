﻿#ifndef STOCKALLDAYSINFO_H
#define STOCKALLDAYSINFO_H

#include <list>
#include <iostream>
#include <memory>
#include <map>
#include <vector>
#include <deque>
 
#include "stkfo_common.h"

#include "stockdayinfo.h"
#include "stk_quoter_api.h"
#include "winner_hq_api.h"

//typedef std::list<T_StockHisDataItem>  T_HisDataItemList;
//typedef std::vector<std::shared_ptr<T_KlineDataItem> >  T_HisDataItemContainer;
typedef std::deque<std::shared_ptr<T_KlineDataItem> >  T_HisDataItemContainer;
typedef std::map<std::string, T_HisDataItemContainer>  T_CodeMapHisDataItemContainer;

class StockAllDaysInfo
{
public:

    StockAllDaysInfo();
    ~StockAllDaysInfo();
    bool Init();

    //std::vector<std::shared_ptr<T_KlineDataItem> > &day_kline_data_container() { return day_kline_data_container_; }

public:
    //list容器，数据类型为一只股票一天的消息，是StockAllDaysInfo的数据成员
    //std::list<StockDayInfo> stockAllDaysInfoList;
    

    //从fileName指定的磁盘路径中将数据一行一行读取出来，每一行初始化一个StockDayInfo对象
    //void LoadDataFromFile(std::string &fileName);

    T_HisDataItemContainer* AppendStockData(PeriodType period_type, const std::string &stk_code, int start_date, int end_date, bool is_index=false);
	     
public:
      
	float GetHisDataLowestMinPrice(PeriodType period_type, const std::string& code, int start_date, int end_date);
	float GetHisDataHighestMaxPrice(PeriodType period_type, const std::string& code, int start_date, int end_date);

public:
     
    T_HisDataItemContainer &GetHisDataContainer(PeriodType period_type, const std::string& code);
    // (stock , data)
    T_CodeMapHisDataItemContainer m5_stock_his_items_;
    T_CodeMapHisDataItemContainer m15_stock_his_items_;
    T_CodeMapHisDataItemContainer m30_stock_his_items_;
    T_CodeMapHisDataItemContainer hour_stock_his_items_;
    T_CodeMapHisDataItemContainer day_stock_his_items_;
    T_CodeMapHisDataItemContainer week_stock_his_items_;
    T_CodeMapHisDataItemContainer mon_stock_his_items_;
#ifndef USE_STK_QUOTER
    std::vector<T_StockHisDataItem> *p_stk_hisdata_item_vector_;
    bool is_fetched_stk_hisdata_;
    //bool is_index_; // such as szzs
#else

#endif 
private:
    //std::vector<std::shared_ptr<T_KlineDataItem> > GetDataItemFromContainer(PeriodType period_type, const std::string& code, int start_date, int end_date);
    std::tuple<int, int> GetDateIndxFromContainer(PeriodType period_type, const std::string& stock, int start_date, int end_date);
private:
#ifdef USE_STK_QUOTER
    StkHisDataDelegate stk_his_data_;
    StkRelHisDataDelegate stk_hisdata_release_;
#else
    WinnerHisHq_ConnectDelegate WinnerHisHq_Connect_;
    WinnerHisHq_DisconnectDelegate WinnerHisHq_DisConnect_;
    WinnerHisHq_GetKDataDelegate  WinnerHisHq_GetKData_;
    T_KDataCallBack  call_back_obj_;
#endif
    std::shared_ptr<PyDataMan> py_data_man_;
     
    //std::vector<std::shared_ptr<T_KlineDataItem> > day_kline_data_container_;
};

#endif // STOCKALLDAYSINFO_H

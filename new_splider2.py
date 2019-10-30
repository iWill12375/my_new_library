import requests
import json
import time
import random
'''
http://query.sse.com.cn/security/stock/getStockListData2.do?&jsonCallBack=jsonpCallback80211
&isPagination=true&stockCode=&csrcCode=&areaName=&stockType=1&pageHelp.cacheSize=1
&pageHelp.beginPage=2&pageHelp.pageSize=25&pageHelp.pageNo=2&pageHelp.endPage=21&_=1572055365342
'''
#构造url = url_p1 + 翻页 + url_p2
url_p1 = "http://query.sse.com.cn/security/stock/getStockListData2.do?&jsonCallBack=jsonpCallback80211 \
&isPagination=true&stockCode=&csrcCode=&areaName=&stockType=1&pageHelp.cacheSize=1 \
&pageHelp.beginPage="
url_p2 = "&pageHelp.pageSize=25&pageHelp.pageNo="
url_p3 = "&pageHelp.endPage="
url_p4 = "1&_=1572055365342"
#构造请求头部
headers = {
    'Accept': 'application/json, text/javascript, */*; q=0.01',
    'Accept-Encoding': 'gzip, deflate',
    'Accept-Language': 'zh-CN,zh;q=0.9',
    'Connection': 'keep-alive',
    'Content-Type': 'application/json',
    #'Host': 'www.szse.cn',
    #'Referer': 'http://www.szse.cn/market/stock/list/index.html',
    'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/78.0.3904.70 Safari/537.36',
    #'X-Request-Type': 'ajax',
    'X-Requested-With': 'XMLHttpRequest'
}
#设置代理ip，静态代理
proxies_list = {
    'http':"39.137.69.9:8080",
    #'http':"39.80.118.178:8060", #disavailable
    #'http':"49.235.244.93:9999", #disavailable
    #'http':"36.7.69.56:8060" #disavailable
}

def struct_url(page):
    return url_p1+"{}".format(page)+url_p2+"{}".format(page)+url_p3+"{}".format(page)+url_p4


def get_HTML(url):
    try:
        r = requests.get(url,proxies=proxies_list,timeout=4)
        r.raise_for_status()
        r.encoding = r.apparent_encoding
        return r.text
    except Exception as e:
        print("splider failed")
        print(e)

def main():
    item = {} #定义一个空字典，保存单元数据
    #爬取结果保存在当前文件夹下一个名为store_d.txt的文件
    try:
        with open('./store_d.txt','a+') as fileobj:
        #深交所A股列表一共有109页，每一页有20行数据
            for i in range(3):
                url = struct_url(i+1)
                original_data = get_HTML(url)
                data0 = json.loads(original_data)
                print("data loading ok")
                data1 = data0[0]['data']
                #每一页20行
                for j in range(20):
                    #打印A股代码、公司名称、所属行业
                    print(data1[j]['agdm']+'\t'+data1[j]['agjc']+'\t'+data1[j]['sshymc'])
                    item['股票代码'] = data1[j]['agdm']
                    item['公司名称'] = data1[j]['agjc']
                    item['所属行业'] = data1[j]['sshymc']
                    fileobj.write(item['股票代码'])
                    fileobj.write(item['公司名称'])
                    fileobj.write(item['所属行业'])
                    fileobj.write('\n')
                #每次循环随机延迟
                time.sleep(random.random()*5)
    except IOError as io:
        print("file open failed")
        print(io)
    except TypeError as te:
        print("type not fit")
        print(te)
    except Exception as e:
        print(e)
main()

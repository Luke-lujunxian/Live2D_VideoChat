#include <helper.hpp>

std::string getHostMacAddress()
{
    QList<QNetworkInterface> nets = QNetworkInterface::allInterfaces();// ��ȡ��������ӿ��б�
    int nCnt = nets.count();
    QString strMacAddr = "";
    for (int i = 0; i < nCnt; i++)
    {
        // ���������ӿڱ�������������в��Ҳ��ǻػ���ַ�������������Ҫ�ҵ�Mac��ַ
        if (nets[i].flags().testFlag(QNetworkInterface::IsUp) && nets[i].flags().testFlag(QNetworkInterface::IsRunning) && !nets[i].flags().testFlag(QNetworkInterface::IsLoopBack))
        {
            strMacAddr = nets[i].hardwareAddress();
            break;
        }
    }
    return strMacAddr.toStdString();
}
//��������������������������������
//��Ȩ����������ΪCSDN������dofaster����ԭ�����£���ѭ CC 4.0 BY - SA ��ȨЭ�飬ת���븽��ԭ�ĳ������Ӽ���������
//ԭ�����ӣ�https ://blog.csdn.net/llmys/article/details/52861545



inline double euclideanDistance(double x1, double y1, double x2, double y2) {
    return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

template<typename T>
struct euclideanPoint {
    T x;
    T y;
};

template<typename T>
inline euclideanPoint<T> rotate(T x, T y, double theta) {
    euclideanPoint<T> temp;
    temp.x = cos(theta) * x + sin(theta) * y;
    temp.y = cos(theta) * y - sin(theta) * x;
    return temp;
}

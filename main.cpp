#include <iostream>
#include <vector>
using namespace std;
struct PCB {
    int ID;//进程编号
    int ArrivalTime;//进程到达时间
    int ServiceTime;//进程运行时间
    int FinishhTime;//进程完成时间
    int Priority;//优先权,数字越大，优先权越高
    int State;//进程状态，'0'代表未完成，'1'代表已完成
};
/*采用动态数组管理就绪队列*/
vector <PCB> Readey;
int sum;//进程数量
int Finish=0;//已经完成的进程数
int NowTime=0;
/*初始化PCB*/
void InitPCB(){
    printf("请输入进程的总数:");
    scanf("%d",&sum);
    for(int i=1;i<=sum;i++) {
        struct PCB p;
        p.ID=i;
        printf("请输入进程%d到达时间:",i);
        scanf("%d", &p.ArrivalTime);
        printf("请输入进程%d运行时间:",i);
        scanf("%d", &p.ServiceTime);
        printf("请输入进程%d的优先权:",i);
        scanf("%d", &p.Priority);
        p.State=0;
        Readey.push_back(p);
    }
}
/*就绪队列中进程按照优先级递降排序*/
bool ProcessSort1(PCB x,PCB y){
    return x.Priority>y.Priority;
}
/*就绪队列中进程按照编号升序排序*/
bool ProcessSort2(PCB x,PCB y){
    return x.ID<y.ID;
}
/*打印当前系统状态*/
void Output(){
    cout<<"*****已经完成进程数："<<Finish<<"*****";
    cout<<"*****正在执行的进程："<<Finish<<"*****";
}
/*进程执行过程*/
void run(){
    sort(Readey.begin(),Readey.end(), ProcessSort1);//按照优先权由高到低排序
    while (Finish<sum){
        vector<PCB>::iterator it=Readey.begin();
        int flag=0;
        //已经到来的进程先执行
        for(vector<PCB>::iterator iter=Readey.begin();iter!=Readey.end();iter++){
            if(NowTime>=(*iter).ArrivalTime&&((*iter).State==0)){
                it=iter;
                flag=1;
                break;
            }
        }
        if(flag) {
            //打印正在运行的进程
            cout << "进程" << (*it).ID << "正在执行" << endl;
            NowTime += (*it).ServiceTime;
            (*it).FinishhTime = NowTime;
            (*it).State = 1;
            Finish++;
        }else{
            NowTime++;
        }
    }
}
/*打印各进程到达时间、完成时间、周转时间，和所有进程的平均周转时间、平均带权周转时间*/
void OutputTime(){
    double ATT;//平均周转时间
    double AWTT;//平均带权周转时间
    sort(Readey.begin(),Readey.end(), ProcessSort2);
    vector<PCB>::iterator it=Readey.begin();
    for(vector<PCB>::iterator iter=Readey.begin();iter!=Readey.end();iter++){
        it=iter;
        cout<<"进程"<<(*it).ID<<"的到达时间："<<(*it).ArrivalTime<<" 完成时间："<<(*it).FinishhTime;
        cout<<" 周转时间："<<(*it).FinishhTime-(*it).ArrivalTime<<endl;
        ATT+=((*it).FinishhTime-(*it).ArrivalTime)*1.0;
        AWTT+=((*it).FinishhTime-(*it).ArrivalTime)*1.0/(*it).ServiceTime;
    }
    printf("所有进程的平均周转时间：%.2lf 平均带权周转时间:%.2lf",ATT/sum,AWTT/sum);
}
int main() {
    InitPCB();
    run();
    OutputTime();
    return 0;
}

#include <pthread.h>
#include <fstream>
#include <cstring>
#include <iostream>
#include <string>
#include <ctime>
#include <vector>
using namespace std;

clock_t start,mid,end;
#define THREAD_NUM 8 

pthread_mutex_t count_mutex = PTHREAD_MUTEX_INITIALIZER;

struct param{

    vector<string> vstr;
    int offset;
    int tidx;

};


void * std_output(void *pa){
    struct param *local = (struct param *) pa;
    vector<string> vstr = local->vstr;
    int offset = local->offset;
    int tidx = local->tidx;

    pthread_mutex_lock(&count_mutex);
    int count = 0;
    int i = offset;
    while(i < vstr.size()){
	//if (tidx==5){
        //    cout << i << endl;
        //}
        count++;
        i+=THREAD_NUM;


     }

    cout << " thread " << tidx << " has " << count << " lines" << endl;
    pthread_mutex_unlock(&count_mutex);

}


int main(){

    start = clock(); 
    ifstream input_data("file.txt");
    int line_num = 0;
    string line;
    vector<string> vstring;
    while(input_data.is_open()){
        if(!input_data.eof()){
            getline(input_data, line);
            vstring.push_back(line);
            line_num++;
        }
        else{
            cout << "total lines:  "<< line_num << endl;
            break;
        }
    }
    input_data.close();
    
    mid = clock();
    //int LINE_PER_THREAD = line_num / THREAD_NUM;
    pthread_t threads[THREAD_NUM];
    for(int i = 0; i < THREAD_NUM; i++){
        struct param *str_param = new param();
        str_param->vstr = vstring;
        str_param->offset = i;
        str_param->tidx = i;
        pthread_create(&threads[i], NULL, std_output, (void *) str_param);
    }

    for(int i = 0; i < THREAD_NUM; i++)
        pthread_join(threads[i], NULL);
    
    end = clock();
    double endtime = (double)(end-start)/CLOCKS_PER_SEC;
    double midtime = (double)(mid-start)/CLOCKS_PER_SEC;
    cout << "midtime: "<<midtime<<"endtime "<<endtime<<endl;
    return 0;
}

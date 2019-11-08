#include <iostream>
#include <vector>
#include <limits.h>

using namespace std;

void swap(int &a,int &b)
{
    int c = b;
    b = a;
    a = c;
}

// work function for quicksort
int work(int edgeu[], int edgev[], int low, int high)
{
    int pivot = high;
    int left = low;
    int right = high - 1;
    while (true)
    {
        while (((left <= right) && (edgeu[left]<edgeu[pivot])) || ((left <=right) && (edgeu[left] == edgeu[pivot])&& (edgev[left] < edgev[pivot]))) left ++;
        while (((right >= left) && (edgeu[right]>edgeu[pivot])) || ((right >= left) && (edgeu[right] == edgeu[pivot] && (edgev[right]> edgev[pivot])))) right --;
        if (left >= right) break;
        swap(edgeu[left], edgeu[right]);
        swap(edgev[left], edgev[right]);
        left ++;
        right --;
    }
    swap(edgeu[left], edgeu[high]);
    swap(edgev[left], edgev[high]);
    return left;
}

void quicksort(int edgeu[], int edgev[], int low, int high)
{
    if (low < high)
    {
        int center = work(edgeu, edgev, low, high);
        quicksort(edgeu, edgev, low, center-1);
        quicksort(edgeu, edgev, center +1, high);
    }
}

int main()
{
    int n, m;
    static int edgeu[100000], edgev[100000],deg[100000] ;
    scanf("%d", &m);
    for (int i =0; i< m; i++) scanf("%d %d", &edgeu[i],&edgev[i]);

    // chuan hoa input nut nho hon dung trc
    for (int i =0; i< m; i++)
    {
        if (edgeu[i] == 0) edgeu[i] = INT_MAX;
        if (edgev[i] == 0) edgev[i] = INT_MAX;
        if (edgeu[i]>edgev[i])
            {
                n=edgeu[i];
                edgeu[i] = edgev[i];
                edgev[i] = n;
            }
    }
    // sort theo thu tu canh tang dan
    quicksort(edgeu, edgev, 0, m-1);

    // save deg and edges with vector
    vector <vector <int> >  data(m+1);
    vector <int> result;
    for (int i=0; i<m; i++)
    {
        deg[edgeu[i]]++;
        if (edgev[i]== INT_MAX) edgev[i] = 0;
        deg[edgev[i]]++;
        data.at(edgeu[i]).push_back(edgev[i]);
        data.at(edgev[i]).push_back(edgeu[i]);
    }
    int k = 0;
    // prufer code function
    while (true)
    {
        for (int i=1; i<=m; i++)
        if (deg[i] == 1)
        {
            k = data.at(i)[0];
            for (int j=0; j<=m; j++)
            {
                if (data.at(k)[j] == i)
                {
                    data.at(k).erase(data.at(k).begin()+j);
                    break;
                }
            }
            result.push_back(k);
            deg[i] --;
            deg[k] --;
            k = -1;
            break;
        } else k = 0;
        if (k != -1) break;
    }
    // in ket qua
    for (int i=0; i< result.size()-1; i++) printf("%d ",result[i]);
    return 0;
}
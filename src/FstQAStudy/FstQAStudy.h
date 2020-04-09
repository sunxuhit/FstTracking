#ifndef FstQAStudy_h
#define FstQAStudy_h

#include <TObject.h>
#include "../FstUtil/FstCons.h"
#include "../FstUtil/FstRawHit.h"
#include "../FstUtil/FstCluster.h"
#include "../FstUtil/FstTrack.h"
#include "../FstUtil/FstEvent.h"
#include <vector>
#include <fstream>

class TFile;
class TChain;
class TTree;
class TH1F;
class TH2F;
class TH3F;
class TProfile;
class TProfile2D;

class FstQAStudy : public TObject
{
  public:
    FstQAStudy();
    ~FstQAStudy();

    void set_list(std::string inputlist)
    {
      mList = inputlist;
    }
    void set_outputfile(std::string outputfile)
    {
      mOutPutFile = outputfile;
    }

    int Init();
    int Make(); // subtract pedestal => signal & find Hits
    int Finish();

    // init input TChain
    bool initChain();

    // Counts
    void initCounts();
    void fillCounts(FstEvent *fstEvent);
    void writeCounts();

    // ADC
    void initAdc_Hits();
    void fillAdc_Hits(std::vector<FstRawHit *> rawHitVec_orig);
    void writeAdc_Hits();

    void initAdc_Clusters();
    void fillAdc_Clusters(std::vector<FstCluster *> clusterVec_orig);
    void writeAdc_Cluster();

    // cluster size
    void initClusterSize();
    void fillClusterSize(std::vector<FstCluster *> clusterVec_orig);
    void writeClusterSize();

    void initClusterSize_TrackClusters();
    void fillClusterSize_TrackClusters(FstEvent *fstEvent);
    void writeClusterSize_TrackClusters();

    // Event Display
    void initEventDisplay_TrackClusters();
    void fillEventDisplay_TrackClusters(FstEvent *fstEvent, int numOfEvent);
    void writeEventDisplay_TrackClusters();

  private:
    std::string mHome, mList;
    std::string mOutPutFile;

    TFile *File_mOutPut;

    // Counts
    TH1F *h_mCounts_Hits[4]; // 0 for FST, 1-3 for IST
    TH1F *h_mCounts_Clusters[4]; // 0 for FST, 1-3 for IST
    TH2F *h_mCounts_Corr[4];
    TH2F *h_mCounts_RPhi[4];

    // ADC
    TH1F *h_mAdcFst_Hits[4]; // 0-3 r_strip
    TH1F *h_mAdcIst_Hits[4]; // 0: FST | 1: ISST

    TH1F *h_mAdcFst_Clusters[4]; // 0-3 r_strip
    TH1F *h_mAdcIst_Clusters[4]; // 0: FST | 1: ISST
    TProfile2D *p_mAdcFst_Column; // cluster mean column vs. hit column
    TProfile2D *p_mAdcFst_Row; // cluster mean row vs. hit row 

    // cluster size
    TProfile *p_mNHitsR_meanColumn; // <R>
    TProfile *p_mNHitsR_meanRow; // <phi>
    TProfile *p_mNHitsPhi_meanColumn;
    TProfile *p_mNHitsPhi_meanRow;
    TProfile *p_mTbDiffR;
    TProfile *p_mTbDiffPhi;

    // Cluster size with track 
    TProfile *p_mNHitsR_rP[4]; // 0: no matching | 1-3 matching within (1-3)*pitchR in r & (1-3)*pitchPhi in phi
    TProfile *p_mNHitsR_phiP[4];
    TProfile *p_mNHitsPhi_rP[4];
    TProfile *p_mNHitsPhi_phiP[4];

    // Event Display
    TH2F *h_mEventDisplay[100]; // 100 random event
    TH2F *h_mEventProjection[100];

    // Input TChain for hits and clusters
    TChain *mChainInPut; // input TTree
    FstEvent *mFstEvent_InPut;
    FstRawHit *mFstRawHit;
    FstCluster *mFstCluster;
    FstTrack *mFstTrack;

    ClassDef(FstQAStudy,1)
};

#endif

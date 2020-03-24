#ifndef FstTracking_h
#define FstTracking_h

#include <TObject.h>
#include <./FstTrackingCons.h>
#include <vector>

class TFile;
class TChain;
class TH1F;
class TH2F;
class TH3F;
class TGraph;

typedef struct
{
  int layer; // 0 for FST, 1-3 for IST
  int sensor;
  int column; // phi for FST, x for IST
  int row; // r_strip for FST, y for IST
  double maxAdc;
  int maxTb;
  bool filled;
} HIT;

typedef struct
{
  int layer; // 0 for FST, 1-3 for IST
  int sensor;
  double meanColumn;
  double meanRow;
  double totAdc;
  int maxTb;
  int clusterSize;
  int clusterSizeR; // R in FST & X in IST && col
  int clusterSizePhi; // Phi in FST & Y in IST && row
  int clusterType; // 0 for ARMDisplay | 1 for Simple | 2 for Scan
} CLUSTER;

class FstTracking : public TObject
{
  public:
    FstTracking();
    ~FstTracking();

    void set_list(std::string inputlist)
    {
      mList = inputlist;
    }
    void set_outputfile(std::string outputfile)
    {
      mOutPutFile = outputfile;
    }

    bool clearSignal();
    bool clearHit();

    int Init();
    bool initChain();
    bool initSignal();
    bool initHit();
    // bool initCluster();

    int Make(); // subtract pedestal => signal & find Hits

    int Finish();

    // pedestal
    bool clearPedestal();
    bool initPedestal();
    bool calPedestal(); // extract pedestal for each ch and fill TGraphs for ped mean & sigma (noise)
    void writePedestal();

    // hit display
    bool initHitDisplay();
    void fillHitDisplay(std::vector<HIT> isthitvec);
    void writeHitDisplay();

    /*
    // cluster with ARMDisplay
    bool clearCluster_ARMDisplay();
    bool initTracking_ARMDisplay();
    bool findCluster_ARMDisplay(std::vector<HIT> isthit_orig);
    void fillTracking_ARMDisplay(std::vector<CLUSTER> istcluster_orig);
    void writeTracking_ARMDisplay();
    */

    // cluster with Simple Algorithm
    bool clearCluster_Simple();
    bool initTracking_Simple();
    bool findCluster_Simple(std::vector<HIT> isthit_orig);
    // void fillTracking_Simple(std::vector<CLUSTER> istcluster_orig);
    void writeTracking_Simple();

  private:
    std::string mHome, mList;
    std::string mOutPutFile;

    TFile *File_mOutPut;

    // Pedestal
    double mPed[FST::numARMs][FST::numPorts][FST::numAPVs][FST::numChannels];
    double mPedStdDev[FST::numARMs][FST::numPorts][FST::numAPVs][FST::numChannels];
    // double pedRMS[FST::numARMs][FST::numPorts][FST::numAPVs][FST::numChannels];

    // Pedestal Display
    TGraph *g_mPedMean[4]; // 0 for FST, 1-3 for IST
    TGraph *g_mPedSigma[4];
    TH2F *h_mPedDisplay[4]; // phi & r_strip

    // Signal
    double mRawSig[FST::numARMs][FST::numPorts][FST::numAPVs][FST::numChannels][FST::numTBins];
    double mSigPedCorr[FST::numARMs][FST::numPorts][FST::numAPVs][FST::numChannels][FST::numTBins];

    // Hit for FST & IST
    std::vector<HIT> mHitsVec; // store hit information for FST & IST after ped subtraction

    // Hit Display
    TH2F *h_mHitDisplay[4]; // 0 for FST, 1-3 for IST
    TH1F *h_mMaxTb[4]; 


    /*
    std::vector<CLUSTER> mClustersVec_ARMDisplay; // cluster with ARMDisplay
    TH1F *h_mXResidual_ARMDisplay;
    TH1F *h_mYResidual_ARMDisplay;
    TH1F *h_mAdc_Layer1_ARMDisplay;
    TH1F *h_mAdc_Layer3_ARMDisplay;
    TH1F *h_mAdcAngleCorr_Layer1_ARMDisplay;
    TH1F *h_mAdcAngleCorr_Layer3_ARMDisplay;
    TH1F *h_mTrackAngle_ARMDisplay;
    */

    std::vector<CLUSTER> mClustersVec_Simple; // cluster with Simple Algorithm
    TH1F *h_mXResidual_Simple;
    TH1F *h_mYResidual_Simple;

    TH1F *h_mAdc_Simple[4];
    TH1F *h_mAdcAngleCorr_Simple[4];
    TH1F *h_mTrackAngle_Simple;

    // Utility for tracking
    int getLayer(int arm, int port); // return layer based on arm & port
    int getSensor(int arm, int port, int apv); // return sensor based on APV and IST/FST
    int getColumn(int arm, int port, int apv, int ch); // return FST/IST column based on arm & port & apv & ch
    int getRow(int arm, int port, int apv, int ch); // return FST/IST row based on arm & port & apv & ch
    int getPhiSeg(int apv, int ch); // return FST Phi segmentation based on apv & ch
    int getRStrip(int apv, int ch); // return FST R strip based on apv & ch
    bool isBadAPV(int arm, int port, int apv);

    TChain *mChainInPut; // input TTree
    int evt_rdo[FST::numARMs][FST::numPorts][FST::numAPVs];
    int evt_arm[FST::numARMs][FST::numPorts][FST::numAPVs];
    int evt_port[FST::numARMs][FST::numPorts][FST::numAPVs];
    int evt_apv[FST::numARMs][FST::numPorts][FST::numAPVs];
    int hit_ch[FST::numARMs][FST::numPorts][FST::numAPVs][FST::numROChannels];
    int hit_tb[FST::numARMs][FST::numPorts][FST::numAPVs][FST::numROChannels];
    int hit_adc[FST::numARMs][FST::numPorts][FST::numAPVs][FST::numROChannels];

    ClassDef(FstTracking,1)
};

#endif
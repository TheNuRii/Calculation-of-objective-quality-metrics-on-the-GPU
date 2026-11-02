#pragma once
#include "CommonDef.h"
#include "xVec4.h"
#include <string_view>

enum class eMetric : int32 {
    UNDEFINED = -1,
    // PSNR - based
    PSNR, 
    SSIM, 
    MSSSIM, 
    IVPSNR,
    // SSIM - based 
    IVSSIM,
    IVMSSSIM,
    __NUM
};

eMetric xStrToMetric(const std::string_view Metric);
std::string xMetricToString(eMetric Metric);

struct xMetricDescr {
    const eMetric           Metric;
    const bool              IsDefault;
    const bool              IsPerCmp;
    const bool              IsPerPic;
    const bool              IsNormalized;
    const std::string_view  Unit;
    const std::string_view  Description;

    constexpr xMetricDescr(eMetric Metric_, bool IsDefault_, bool IsPerCmp_, bool IsPerPic_, 
        bool IsNormalized_, std::string_view Unit_, std::string_view Description_)
    : Metric(Metric_), IsDefault(IsDefault_), IsPerCmp(IsPerCmp_), IsPerPic(IsPerPic_), IsNormalized(IsNormalized_), Unit(Unit_), Description(Description_) {}
};


struct xMetricInfo {
    static constexpr int32 MetricNum = (int32)eMetric::__NUM;
    static constexpr int32 MaxMetricNameLen = 8;

    static constexpr xMetricDescr Metrics[(int32)eMetric::__NUM] = {
        //           Metric  D  C  P  N  Unit  Description                                                            },
    { eMetric::    PSNR, 1, 1, 0, 0, "dB", "Peak Signal-to-Noise Ratio"                                                      },
    { eMetric::  IVPSNR, 1, 0, 1, 0, "dB", "Immersive Video - Peak Signal-to-Noise Ratio"                                    },
    { eMetric::    SSIM, 0, 1, 0, 1, "  ", "Structural Similarity Index Measure"                                             },
    { eMetric::  MSSSIM, 0, 1, 0, 1, "  ", "Multi Scale Structural Similarity Index Measure"                                 },
    { eMetric::  IVSSIM, 1, 0, 1, 1, "  ", "Immersive Video - Structural Similarity Index Measure"                           },
    { eMetric::IVMSSSIM, 0, 0, 1, 1, "  ", "Immersive Video - Multi Scale Structural Similarity Index Measure"               },
    };
};

class xMetricStat {
protected:
    eMetric     m_Metric    = eMetric::UNDEFINED;
    std::string m_SuffixCmp = "";
    std::string m_SuffixPic = "";
    int32V4     m_CmpWeightsAverage = { 0, 0, 0, 0 };
    flt64       m_CmpWeightAverageInvDenom = 0.0;
    bool        m_MaskMode = false;
    uint64      m_SumTicks = 0;
    tDurationMS m_AvgDuration;
    std::vector<flt64V4> m_ValCmp;
    std::vector<flt64  > m_ValPic;
    flt64V4     m_AvgCmp;
    flt64       m_AvgPic;  
    bool        m_AnyFake  = false;
    bool        m_Enabled  = false;

public:
    eMetric getMetric () const { return m_Metric ; }
    bool    getEnabled() const { return m_Enabled; }

    void initMetric  (eMetric Metric, int32 NumFrames);
    void initSuffixes(bool UseMask, bool UseRGB);

    void initCmpWeightsAverage(const int32V4& CmpWeightsAverage);
    void setPerCmpMeric       (const flt64V4& PerCmpMetric, int32 FrameIdx);
    void setPerPicMeric       (flt64 PerPicMetric, int32 FrameIdx) { m_ValPic[FrameIdx] = PerPicMetric; }
    void setAnyFake           (bool AnyFake) { m_AnyFake = AnyFake; }
    void addTicks             (uint64 DurationTicks) { m_SumTicks += DurationTicks; }
};
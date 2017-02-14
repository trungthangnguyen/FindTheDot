//
//  MyAdDefines.h
//
//
//  Created by Hieu Nguyen Trung on 3/1/15.
//
//

#pragma mark
// MARK: namespace
#define MYADS_NAMESPACE                 HLOVEK_MYADS
#define MYADS_NAMESPACE_BEGIN           namespace MYADS_NAMESPACE {
#define MYADS_NAMESPACE_END             }

typedef enum {
    kMyAdsBannerPositionTop,
    kMyAdsBannerPositionBottom,
} kMyAdsBannerPosition;

#pragma mark
// MARK: MyAds
#define MYADS_RATIO_AD_MOB_BANNER       0.75f
#define MYADS_RATIO_AD_MOB_INTERSTITIAL 1.75f
#define MYADS_BANNER_POSITION           kMyAdsBannerPositionBottom

#pragma mark
// MARK: AdMob (Google)
#define MYADMOB_AD_UNIT_ID_BANNER       @"ca-app-pub-9247885086164337/1376688804"
#define MYADMOB_AD_UNIT_ID_INTERSTITIAL @"ca-app-pub-9247885086164337/2853422007"
#define MYADMOB_BANNER_SIZE_IPHONE      kGADAdSizeBanner
#define MYADMOB_BANNER_SIZE_IPAD        kGADAdSizeLeaderboard

// -- test device array --
#define MYADMOB_TEST_DEVICES // neu muon tat test devices thi comment dong nay lai
#if defined(MYADMOB_TEST_DEVICES)

#define MYADMOB_TEST_DEVICES_ARRAY      [NSArray arrayWithObjects:              \
                                        @"4fd770d90cf27fad9fab0dbbf4164a18",    \
                                        @"e04b368f8b4c1a0d619adc59a49c27f6",    \
                                        @"0924fc2aea6a811d88fd3d07c9f4c5e5",    \
                                        @"c2d91e583021930d33532f741baebd9b",    \
                                        nil]                                    \

#else

#define MYADMOB_TEST_DEVICES_ARRAY      nil

#endif
// ----

#pragma mark
// MARK: iAd (Apple)

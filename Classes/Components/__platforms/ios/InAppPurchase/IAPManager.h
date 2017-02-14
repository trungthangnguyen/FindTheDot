//
//  IAPManager.h
//  CanYouTap100
//
//  Created by Hieu Nguyen Trung on 11/25/15.
//
//

#import <Foundation/Foundation.h>
#import "IAPHelper.h"

#include "../../../MyInAppPurchase/MyInAppPurchaseDelegate.h"

@interface IAPManager : IAPHelper {
    MyInAppPurchaseDelegate *_delegate;
    NSArray                 *_products;
    NSString                *_pendingProduct;
}
@property(nonatomic, assign) MyInAppPurchaseDelegate *delegate;
@property(nonatomic, retain) NSArray *products;
@property(nonatomic, retain) NSString *pendingProduct;

- (BOOL) isProductPurchased:(NSString *) identifier;

- (void) onRestorePurchased;
- (void) onPurchaseProduct:(NSString *) identifier;
- (void) reloadPurchase;
- (void) reloadPurchaseAndBuyProduct:(NSString *) identifier;

@end

@interface IAPManager(Override)

- (void) request:(SKRequest *) request didFailWithError:(NSError *) error;
- (void) completeTransaction:(SKPaymentTransaction *) transaction;
- (void) restoreTransaction:(SKPaymentTransaction *) transaction;
- (void) failedTransaction:(SKPaymentTransaction *) transaction;

@end

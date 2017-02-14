//
//  IAPHelper.h
//  In App Rage
//
//  Created by Ray Wenderlich on 9/5/12.
//  Copyright (c) 2012 Razeware LLC. All rights reserved.
//

#import <StoreKit/StoreKit.h>

UIKIT_EXTERN NSString *const IAPHelperProductPurchasedNotification;

typedef void (^RequestProductsCompletionHandler)(BOOL success, NSArray * products);

@interface IAPHelper : NSObject

- (id)initWithProductIdentifiers:(NSSet *)productIdentifiers;

- (void)requestProductsWithCompletionHandler:(RequestProductsCompletionHandler)completionHandler;
- (void)buyProduct:(SKProduct *)product;
- (void)completeTransaction:(SKPaymentTransaction *) transaction;
- (void)restoreTransaction:(SKPaymentTransaction *) transaction;
- (void)failedTransaction:(SKPaymentTransaction *) transaction;
- (void)failedRestoreTransactionWithError:(NSError *)error;
- (void)request:(SKRequest *)request didFailWithError:(NSError *)error;

- (BOOL)productPurchased:(NSString *)productIdentifier;
- (void)restoreCompletedTransactions;

@end
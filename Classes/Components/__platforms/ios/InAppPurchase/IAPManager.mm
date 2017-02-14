//
//  IAPManager.m
//  CanYouTap100
//
//  Created by Hieu Nguyen Trung on 11/25/15.
//
//

#import "IAPManager.h"

@implementation IAPManager
@synthesize delegate = _delegate;
@synthesize products = _products;
@synthesize pendingProduct = _pendingProduct;

#pragma mark Purchase
- (SKProduct *) productById:(NSString *) identifier array:(NSArray *) products
{
    for (SKProduct *skProduct in products) {
        if ([identifier isEqualToString:skProduct.productIdentifier]) {
            return skProduct;
        }
    }
    
    return nil;
}

- (BOOL) isProductPurchased:(NSString *) identifier
{
    return [self productPurchased:identifier];
}

- (void) onRestorePurchased
{
    [self restoreCompletedTransactions];
}

- (void) onPurchaseProduct:(NSString *) identifier
{
    if (![self isProductPurchased:identifier]) {
        if (_products.count) {
            [self buyProduct:[self productById:identifier array:_products]];
        } else {
            [self reloadPurchaseAndBuyProduct:identifier];
        }
    }
}

- (void) reloadPurchase
{
    [self reloadPurchaseAndBuyProduct:nil];
}

- (void) reloadPurchaseAndBuyProduct:(NSString *) identifier
{
    self.products = nil;
    self.pendingProduct = identifier;
    
    [self requestProductsWithCompletionHandler:^(BOOL success, NSArray *products) {
        if (success) {
            self.products = products;
            
            if (_pendingProduct) {
                [self buyProduct:[self productById:_pendingProduct array:_products]];
            }
        }
    }];
}

#pragma mark Override
- (void)request:(SKRequest *)request didFailWithError:(NSError *)error {
    [super request:request didFailWithError:error];
    
    if (_delegate) {
        _delegate->requestDidFailWithError(error.code);
    }
}

- (void)completeTransaction:(SKPaymentTransaction *)transaction {
    [super completeTransaction:transaction];
    
    if (_delegate) {
        _delegate->completeTransaction([transaction.transactionIdentifier UTF8String]);
    }
}

- (void)restoreTransaction:(SKPaymentTransaction *)transaction {
    [super restoreTransaction:transaction];
    
    if (_delegate) {
        _delegate->restoreTransaction([transaction.transactionIdentifier UTF8String]);
    }
}

- (void)failedTransaction:(SKPaymentTransaction *)transaction {
    [super failedTransaction:transaction];
    
    if (_delegate) {
        _delegate->failedTransaction([transaction.transactionIdentifier UTF8String]);
    }
}

- (void)failedRestoreTransactionWithError:(NSError *)error{
    [super failedRestoreTransactionWithError:error];
    
    if (_delegate) {
        _delegate->failedRestoreTransactionWithError(error.code);
    }
}

#pragma mark dealloc
- (void) dealloc
{
    [_products release];
    [_pendingProduct release];
    
    [super dealloc];
}

@end

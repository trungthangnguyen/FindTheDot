//
//  MyInAppPurchaseDelegate.h
//  CanYouTap100
//
//  Created by Hieu Nguyen Trung on 11/26/15.
//
//

class MyInAppPurchaseDelegate {
    
public:
    virtual void requestDidFailWithError(long code) = 0;
    virtual void completeTransaction(const char *transactionIdentifier) = 0;
    virtual void restoreTransaction(const char *transactionIdentifier) = 0;
    virtual void failedTransaction(const char *transactionIdentifier) = 0;
    virtual void failedRestoreTransactionWithError(long code) = 0;
};

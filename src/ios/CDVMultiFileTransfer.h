/*
 Licensed to the Apache Software Foundation (ASF) under one
 or more contributor license agreements.  See the NOTICE file
 distributed with this work for additional information
 regarding copyright ownership.  The ASF licenses this file
 to you under the Apache License, Version 2.0 (the
 "License"); you may not use this file except in compliance
 with the License.  You may obtain a copy of the License at

 http://www.apache.org/licenses/LICENSE-2.0

 Unless required by applicable law or agreed to in writing,
 software distributed under the License is distributed on an
 "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 KIND, either express or implied.  See the License for the
 specific language governing permissions and limitations
 under the License.
 */

#import <Foundation/Foundation.h>
#import <Cordova/CDVPlugin.h>
#import "CDVFile.h"

enum CDVMultiFileTransferError {
    FILE_NOT_FOUND_ERR = 1,
    INVALID_URL_ERR = 2,
    CONNECTION_ERR = 3,
    CONNECTION_ABORTED = 4,
    NOT_MODIFIED = 5
};
typedef int CDVMultiFileTransferError;

enum CDVMultiFileTransferDirection {
    CDV_TRANSFER_UPLOAD = 1,
    CDV_TRANSFER_DOWNLOAD = 2,
};
typedef int CDVMultiFileTransferDirection;

// Magic value within the options dict used to set a cookie.
extern NSString* const kOptionsKeyCookie;

@interface CDVMultiFileTransfer : CDVPlugin {}

- (void)upload:(CDVInvokedUrlCommand*)command;
- (void)download:(CDVInvokedUrlCommand*)command;
- (NSString*)escapePathComponentForUrlString:(NSString*)urlString;

// Visible for testing.
- (NSURLRequest*)requestForUploadCommand:(CDVInvokedUrlCommand*)command fileData:(NSArray *)fileDatas;
- (NSMutableDictionary*)createFileTransferError:(int)code AndSource:(NSString*)source AndTarget:(NSString*)target;

- (NSMutableDictionary*)createFileTransferError:(int)code
                                      AndSource:(NSString*)source
                                      AndTarget:(NSString*)target
                                  AndHttpStatus:(int)httpStatus
                                        AndBody:(NSString*)body;
@property (nonatomic, strong) NSOperationQueue* queue;
@property (readonly) NSMutableDictionary* activeTransfers;
@end

@class CDVMultiFileTransferEntityLengthRequest;

@interface CDVMultiFileTransferDelegate : NSObject {}

- (void)updateBytesExpected:(long long)newBytesExpected;
- (void)cancelTransfer:(NSURLConnection*)connection;

@property (strong) NSMutableData* responseData; // atomic
@property (nonatomic, strong) NSDictionary* responseHeaders;
@property (nonatomic, assign) UIBackgroundTaskIdentifier backgroundTaskID;
@property (nonatomic, strong) CDVMultiFileTransfer* command;
@property (nonatomic, assign) CDVMultiFileTransferDirection direction;
@property (nonatomic, strong) NSURLConnection* connection;
@property (nonatomic, copy) NSString* callbackId;
@property (nonatomic, copy) NSString* objectId;
@property (nonatomic, copy) NSString* source;
@property (nonatomic, copy) NSString* target;
@property (nonatomic, copy) NSURL* targetURL;
@property (nonatomic, copy) NSString* mimeType;
@property (assign) int responseCode; // atomic
@property (nonatomic, assign) long long bytesTransfered;
@property (nonatomic, assign) long long bytesExpected;
@property (nonatomic, assign) BOOL trustAllHosts;
@property (strong) NSFileHandle* targetFileHandle;
@property (nonatomic, strong) CDVMultiFileTransferEntityLengthRequest* entityLengthRequest;
@property (nonatomic, strong) CDVFile *filePlugin;

@end

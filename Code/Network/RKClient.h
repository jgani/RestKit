//
//  RKClient.h
//  RestKit
//
//  Created by Blake Watters on 7/28/09.
//  Copyright 2009 Two Toasters. All rights reserved.
//

#import "RKRequest.h"
#import "RKParams.h"
#import "RKResponse.h"
#import "NSDictionary+RKRequestSerialization.h"

/**
 * RKClient exposes the low level client interface for working
 * with HTTP servers and RESTful services. It wraps the request/response
 * cycle with a clean, simple interface.
 */
@interface RKClient : NSObject {
	NSString* _baseURL;
	NSString* _username;
	NSString* _password;
	NSMutableDictionary* _HTTPHeaders;
}

/**
 * The base URL all resources are nested underneath
 */
@property(nonatomic, retain) NSString* baseURL;

/**
 * The username to use for authentication via HTTP AUTH
 */
@property(nonatomic, retain) NSString* username;

/**
 * The password to use for authentication via HTTP AUTH
 */
@property(nonatomic, retain) NSString* password;

/**
 * A dictionary of headers to be sent with each request
 */
@property(nonatomic, readonly) NSDictionary* HTTPHeaders;

/**
 * Return the configured singleton instance of the Rest client
 */
// TODO: Should be sharedClient/globalClient?
+ (RKClient*)client;

/**
 * Set the shared singleton issue of the Rest client
 */
// TODO: Should be sharedClient/globalClient?
+ (void)setClient:(RKClient*)client;

/**
 * Return a Rest client scoped to a particular base URL. If the singleton client is nil, the return client is set as the singleton
 */
+ (RKClient*)clientWithBaseURL:(NSString*)baseURL;

/**
 * Return a Rest client scoped to a particular base URL with a set of HTTP AUTH credentials. If the singleton client is nil, the return client is set as the singleton
 */
+ (RKClient*)clientWithBaseURL:(NSString*)baseURL username:(NSString*)username password:(NSString*)password;

/**
 *  Will check for network connectivity (to google.com)
 */
- (BOOL)isNetworkAvailable;

/**
 * Adds an HTTP header to each request dispatched through the Rest client
 */
- (void)setValue:(NSString*)value forHTTPHeaderField:(NSString*)header;

/**
 * Returns a resource path with a dictionary of query parameters URL encoded and appended
 */
- (NSString*)resourcePath:(NSString*)resourcePath withQueryParams:(NSDictionary*)queryParams;

/**
 * Returns a NSURL by adding a resource path to the base URL
 */
- (NSURL*)URLForResourcePath:(NSString*)resourcePath;

/**
 * Returns a NSURL by adding a resource path to the base URL and appending a URL encoded set of query parameters
 */
- (NSURL*)URLForResourcePath:(NSString *)resourcePath queryParams:(NSDictionary*)queryParams;

/**
 * Return a request object targetted at a resource path relative to the base URL. By default the method is set to GET
 * All headers set on the client will automatically be applied to the request as well.
 */
- (RKRequest*)requestWithResourcePath:(NSString*)resourcePath delegate:(id)delegate callback:(SEL)callback;

///////////////////////////////////////////////////////////////////////////////////////////////////////////
// Asynchronous Helper Methods
///////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * These methods are provided as a convenience to cover the common asynchronous request tasks. All other request
 * needs should instantiate a request via requestWithResourcePath:delegate:callback and work with the RKRequest
 * object directly.
 */

/**
 * Fetch a resource via an HTTP GET and invoke a callback with the result
 */
- (RKRequest*)get:(NSString*)resourcePath delegate:(id)delegate callback:(SEL)callback;

/**
 * Fetch a resource via an HTTP GET with a dictionary of params and invoke a callback with the resulting payload
 *
 * Note that this request _only_ allows NSDictionary objects as the params. The dictionary will be coerced into a URL encoded
 * string and then appended to the resourcePath as the query string of the request.
 */
- (RKRequest*)get:(NSString*)resourcePath queryParams:(NSDictionary*)queryParams delegate:(id)delegate callback:(SEL)callback;

/**
 * Create a resource via an HTTP POST with a set of form parameters and invoke a callback with the resulting payload
 */
- (RKRequest*)post:(NSString*)resourcePath params:(NSObject<RKRequestSerializable>*)params delegate:(id)delegate callback:(SEL)callback;

/**
 * Update a resource via an HTTP PUT and invoke a callback with the resulting payload
 */
- (RKRequest*)put:(NSString*)resourcePath params:(NSObject<RKRequestSerializable>*)params delegate:(id)delegate callback:(SEL)callback;

/**
 * Destroy a resource via an HTTP DELETE and invoke a callback with the resulting payload
 */
- (RKRequest*)delete:(NSString*)resourcePath delegate:(id)delegate callback:(SEL)callback;

@end

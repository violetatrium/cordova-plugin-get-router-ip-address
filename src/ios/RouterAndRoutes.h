//
//  RouterAndRoutes.h
//  NetworkTests
//
//  Created by Alexandre Vallières-Lagacé on 2015-01-13.
//
//

#ifndef NetworkTests_GetRouter_h
#define NetworkTests_GetRouter_h

#include <stdio.h>
#import <sys/socket.h>
#import <netinet/in.h>
#import <net/if_dl.h>
#import <sys/sysctl.h>

#include "/usr/include/net/route.h"

#define RTF_PRCLONING	0x10000		/* protocol requires cloning */
#define RTF_WASCLONED	0x20000		/* route generated through cloning */
#define RTF_PROTO3	0x40000		/* protocol specific routing flag */

#define RTAX_DST	0	/* destination sockaddr present */
#define RTAX_GATEWAY	1	/* gateway sockaddr present */
#define RTAX_NETMASK	2	/* netmask sockaddr present */
#define RTAX_GENMASK	3	/* cloning mask sockaddr present */
#define RTAX_IFP	4	/* interface name sockaddr present */
#define RTAX_IFA	5	/* interface addr sockaddr present */
#define RTAX_AUTHOR	6	/* sockaddr for author of redirect */
#define RTAX_BRD	7	/* for NEWADDR, broadcast or p-p dest addr */
#define RTAX_MAX	8	/* size of array to allocate */

#define RTA_DST		0x1	/* destination sockaddr present */
#define RTA_GATEWAY	0x2	/* gateway sockaddr present */
#define RTA_NETMASK	0x4	/* netmask sockaddr present */
#define RTA_GENMASK	0x8	/* cloning mask sockaddr present */
#define RTA_IFP		0x10	/* interface name sockaddr present */
#define RTA_IFA		0x20	/* interface addr sockaddr present */
#define RTA_AUTHOR	0x40	/* sockaddr for author of redirect */
#define RTA_BRD		0x80	/* for NEWADDR, broadcast or p-p dest addr */


@interface Route_Info : NSObject
{
    struct sockaddr     m_addrs[RTAX_MAX];
    struct rt_msghdr2   m_rtm;
    int                 m_len;      /* length of the sockaddr array */
}
- initWithRtm: (struct rt_msghdr2*) rtm;

+ (NSMutableArray*) getRoutes;
+ (Route_Info*) getRoute:(struct rt_msghdr2 *)rtm;

- (NSString*) getDestination;
- (NSString*) getNetmask;
- (NSString*) getGateway;
- (NSString*) getAddrStringByIndex: (int)rtax_index;

+ (NSString*) getRouterIpAddress;

- (void) setAddr:(struct sockaddr*)sa index:(int)rtax_index;
@end

#endif

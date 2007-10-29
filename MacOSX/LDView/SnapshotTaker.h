//
//  SnapshotTaker.h
//  LDView
//
//  Created by Travis Cobbs on 10/14/07.
//  Copyright 2007 __MyCompanyName__. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#include <TRE/TREGL.h>

#include <LDLib/LDSnapshotTaker.h>

class LDSnapshotTaker;
class LDrawModelViewer;

@interface SnapshotTaker : NSObject {
	LDSnapshotTaker *ldSnapshotTaker;
	CGLPBufferObj pbuffer;
	CGLContextObj context;
}

- (id)init;
- (id)initWithModelViewer:(LDrawModelViewer *)modelViewer sharedContext:(NSOpenGLContext *)sharedContext;

- (void)setImageType:(LDSnapshotTaker::ImageType)value;
- (void)setTrySaveAlpha:(bool)value;
- (void)setAutoCrop:(bool)value;
- (bool)saveFile;
- (bool)saveFile:(NSString *)filename width:(int)width height:(int)height zoomToFit:(bool)zoomToFit;

@end
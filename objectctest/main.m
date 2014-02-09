#import  "main.h"

@implementation HelloClass
- (void) sayHello {
	printf("hello from HelloClass\n\n");
}

- (id) init {
	[super init];
	return self;
}
@end

int main(void)
{
	printf("hello\n\n");

	//HelloClass *hc = [[HelloClass alloc] init];
	HelloClass *hc = [HelloClass new];
	printf("class initialized\n\n");
	[hc sayHello];
	printf("exiting\n\n");
	return 0;
}

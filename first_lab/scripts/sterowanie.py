#!/usr/bin/env python
import rospy
import sys
from geometry_msgs.msg import Twist

def steer(key):
	sTwist = Twist()
	if key == 'a':
		sTwist.angular.z = 0.5
	elif key == 'd':
		sTwist.angular.z = -0.5
	elif key == 'w':
		sTwist.linear.x = 1
	elif key == 's':
		sTwist.linear.x = -1
	return sTwist

def sterowanie():
	pub = rospy.Publisher('turtle_namespace/turtle1/cmd_vel', Twist, queue_size = 10)
	rospy.init_node('sterowanie')
	#rate = rospy.Rate(10)
	#msg = None
	while not rospy.is_shutdown():
		key = raw_input('Steer the turtle using wasd keys:')
		rospy.loginfo("You entered:" + str(key))
		msg = steer(key)
		if msg:		
			pub.publish(msg)
		#msg = None
		#rate.sleep()

if __name__ == '__main__':
	try:
		sterowanie()
	except rospy.ROSInterruptException:
		pass



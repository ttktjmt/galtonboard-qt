QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    galtonboard.cpp \
    include/box2d/Collision/Shapes/b2ChainShape.cpp \
    include/box2d/Collision/Shapes/b2CircleShape.cpp \
    include/box2d/Collision/Shapes/b2EdgeShape.cpp \
    include/box2d/Collision/Shapes/b2PolygonShape.cpp \
    include/box2d/Collision/b2BroadPhase.cpp \
    include/box2d/Collision/b2CollideCircle.cpp \
    include/box2d/Collision/b2CollideEdge.cpp \
    include/box2d/Collision/b2CollidePolygon.cpp \
    include/box2d/Collision/b2Collision.cpp \
    include/box2d/Collision/b2Distance.cpp \
    include/box2d/Collision/b2DynamicTree.cpp \
    include/box2d/Collision/b2TimeOfImpact.cpp \
    include/box2d/Common/b2BlockAllocator.cpp \
    include/box2d/Common/b2Draw.cpp \
    include/box2d/Common/b2Math.cpp \
    include/box2d/Common/b2Settings.cpp \
    include/box2d/Common/b2StackAllocator.cpp \
    include/box2d/Common/b2Timer.cpp \
    include/box2d/Dynamics/Contacts/b2ChainAndCircleContact.cpp \
    include/box2d/Dynamics/Contacts/b2ChainAndPolygonContact.cpp \
    include/box2d/Dynamics/Contacts/b2CircleContact.cpp \
    include/box2d/Dynamics/Contacts/b2Contact.cpp \
    include/box2d/Dynamics/Contacts/b2ContactSolver.cpp \
    include/box2d/Dynamics/Contacts/b2EdgeAndCircleContact.cpp \
    include/box2d/Dynamics/Contacts/b2EdgeAndPolygonContact.cpp \
    include/box2d/Dynamics/Contacts/b2PolygonAndCircleContact.cpp \
    include/box2d/Dynamics/Contacts/b2PolygonContact.cpp \
    include/box2d/Dynamics/Joints/b2DistanceJoint.cpp \
    include/box2d/Dynamics/Joints/b2FrictionJoint.cpp \
    include/box2d/Dynamics/Joints/b2GearJoint.cpp \
    include/box2d/Dynamics/Joints/b2Joint.cpp \
    include/box2d/Dynamics/Joints/b2MotorJoint.cpp \
    include/box2d/Dynamics/Joints/b2MouseJoint.cpp \
    include/box2d/Dynamics/Joints/b2PrismaticJoint.cpp \
    include/box2d/Dynamics/Joints/b2PulleyJoint.cpp \
    include/box2d/Dynamics/Joints/b2RevoluteJoint.cpp \
    include/box2d/Dynamics/Joints/b2RopeJoint.cpp \
    include/box2d/Dynamics/Joints/b2WeldJoint.cpp \
    include/box2d/Dynamics/Joints/b2WheelJoint.cpp \
    include/box2d/Dynamics/b2Body.cpp \
    include/box2d/Dynamics/b2ContactManager.cpp \
    include/box2d/Dynamics/b2Fixture.cpp \
    include/box2d/Dynamics/b2Island.cpp \
    include/box2d/Dynamics/b2World.cpp \
    include/box2d/Dynamics/b2WorldCallbacks.cpp \
    include/box2d/Rope/b2Rope.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    galtonboard.h \
    include/box2d/Collision/Shapes/b2ChainShape.h \
    include/box2d/Collision/Shapes/b2CircleShape.h \
    include/box2d/Collision/Shapes/b2EdgeShape.h \
    include/box2d/Collision/Shapes/b2PolygonShape.h \
    include/box2d/Collision/Shapes/b2Shape.h \
    include/box2d/Collision/b2BroadPhase.h \
    include/box2d/Collision/b2Collision.h \
    include/box2d/Collision/b2Distance.h \
    include/box2d/Collision/b2DynamicTree.h \
    include/box2d/Collision/b2TimeOfImpact.h \
    include/box2d/Common/b2BlockAllocator.h \
    include/box2d/Common/b2Draw.h \
    include/box2d/Common/b2GrowableStack.h \
    include/box2d/Common/b2Math.h \
    include/box2d/Common/b2Settings.h \
    include/box2d/Common/b2StackAllocator.h \
    include/box2d/Common/b2Timer.h \
    include/box2d/Dynamics/Contacts/b2ChainAndCircleContact.h \
    include/box2d/Dynamics/Contacts/b2ChainAndPolygonContact.h \
    include/box2d/Dynamics/Contacts/b2CircleContact.h \
    include/box2d/Dynamics/Contacts/b2Contact.h \
    include/box2d/Dynamics/Contacts/b2ContactSolver.h \
    include/box2d/Dynamics/Contacts/b2EdgeAndCircleContact.h \
    include/box2d/Dynamics/Contacts/b2EdgeAndPolygonContact.h \
    include/box2d/Dynamics/Contacts/b2PolygonAndCircleContact.h \
    include/box2d/Dynamics/Contacts/b2PolygonContact.h \
    include/box2d/Dynamics/Joints/b2DistanceJoint.h \
    include/box2d/Dynamics/Joints/b2FrictionJoint.h \
    include/box2d/Dynamics/Joints/b2GearJoint.h \
    include/box2d/Dynamics/Joints/b2Joint.h \
    include/box2d/Dynamics/Joints/b2MotorJoint.h \
    include/box2d/Dynamics/Joints/b2MouseJoint.h \
    include/box2d/Dynamics/Joints/b2PrismaticJoint.h \
    include/box2d/Dynamics/Joints/b2PulleyJoint.h \
    include/box2d/Dynamics/Joints/b2RevoluteJoint.h \
    include/box2d/Dynamics/Joints/b2RopeJoint.h \
    include/box2d/Dynamics/Joints/b2WeldJoint.h \
    include/box2d/Dynamics/Joints/b2WheelJoint.h \
    include/box2d/Dynamics/b2Body.h \
    include/box2d/Dynamics/b2ContactManager.h \
    include/box2d/Dynamics/b2Fixture.h \
    include/box2d/Dynamics/b2Island.h \
    include/box2d/Dynamics/b2TimeStep.h \
    include/box2d/Dynamics/b2World.h \
    include/box2d/Dynamics/b2WorldCallbacks.h \
    include/box2d/Rope/b2Rope.h \
    include/box2d/b2_api.h \
    include/box2d/b2_block_allocator.h \
    include/box2d/b2_body.h \
    include/box2d/b2_broad_phase.h \
    include/box2d/b2_chain_shape.h \
    include/box2d/b2_circle_shape.h \
    include/box2d/b2_collision.h \
    include/box2d/b2_common.h \
    include/box2d/b2_contact.h \
    include/box2d/b2_contact_manager.h \
    include/box2d/b2_distance.h \
    include/box2d/b2_distance_joint.h \
    include/box2d/b2_draw.h \
    include/box2d/b2_dynamic_tree.h \
    include/box2d/b2_edge_shape.h \
    include/box2d/b2_fixture.h \
    include/box2d/b2_friction_joint.h \
    include/box2d/b2_gear_joint.h \
    include/box2d/b2_growable_stack.h \
    include/box2d/b2_joint.h \
    include/box2d/b2_math.h \
    include/box2d/b2_motor_joint.h \
    include/box2d/b2_mouse_joint.h \
    include/box2d/b2_polygon_shape.h \
    include/box2d/b2_prismatic_joint.h \
    include/box2d/b2_pulley_joint.h \
    include/box2d/b2_revolute_joint.h \
    include/box2d/b2_rope.h \
    include/box2d/b2_settings.h \
    include/box2d/b2_shape.h \
    include/box2d/b2_stack_allocator.h \
    include/box2d/b2_time_of_impact.h \
    include/box2d/b2_time_step.h \
    include/box2d/b2_timer.h \
    include/box2d/b2_types.h \
    include/box2d/b2_weld_joint.h \
    include/box2d/b2_wheel_joint.h \
    include/box2d/b2_world.h \
    include/box2d/b2_world_callbacks.h \
    include/box2d/box2d.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    include/box2d/Box2DConfig.cmake \
    include/box2d/CMakeLists.txt

# DO NOT EDIT
# This makefile makes sure all linkable targets are
# up-to-date with anything they link to
default:
	echo "Do not invoke directly"

# Rules to remove targets that are older than anything to which they
# link.  This forces Xcode to relink the targets from scratch.  It
# does not seem to check these dependencies itself.
PostBuild.geometry_test.Debug:
/Users/mac/my\ mac/graphics.com391/Labs/lab06/build/bin/geometry_test:
	/bin/rm -f /Users/mac/my\ mac/graphics.com391/Labs/lab06/build/bin/geometry_test


PostBuild.lightning_test.Debug:
/Users/mac/my\ mac/graphics.com391/Labs/lab06/build/bin/lightning_test:
	/bin/rm -f /Users/mac/my\ mac/graphics.com391/Labs/lab06/build/bin/lightning_test


PostBuild.scene_graph_test.Debug:
/Users/mac/my\ mac/graphics.com391/Labs/lab06/build/bin/scene_graph_test:
	/bin/rm -f /Users/mac/my\ mac/graphics.com391/Labs/lab06/build/bin/scene_graph_test


PostBuild.triangle_test.Debug:
/Users/mac/my\ mac/graphics.com391/Labs/lab06/build/bin/triangle_test:
	/bin/rm -f /Users/mac/my\ mac/graphics.com391/Labs/lab06/build/bin/triangle_test


PostBuild.window_test.Debug:
/Users/mac/my\ mac/graphics.com391/Labs/lab06/build/bin/window_test:
	/bin/rm -f /Users/mac/my\ mac/graphics.com391/Labs/lab06/build/bin/window_test


PostBuild.geometry_test.Release:
/Users/mac/my\ mac/graphics.com391/Labs/lab06/build/bin/geometry_test:
	/bin/rm -f /Users/mac/my\ mac/graphics.com391/Labs/lab06/build/bin/geometry_test


PostBuild.lightning_test.Release:
/Users/mac/my\ mac/graphics.com391/Labs/lab06/build/bin/lightning_test:
	/bin/rm -f /Users/mac/my\ mac/graphics.com391/Labs/lab06/build/bin/lightning_test


PostBuild.scene_graph_test.Release:
/Users/mac/my\ mac/graphics.com391/Labs/lab06/build/bin/scene_graph_test:
	/bin/rm -f /Users/mac/my\ mac/graphics.com391/Labs/lab06/build/bin/scene_graph_test


PostBuild.triangle_test.Release:
/Users/mac/my\ mac/graphics.com391/Labs/lab06/build/bin/triangle_test:
	/bin/rm -f /Users/mac/my\ mac/graphics.com391/Labs/lab06/build/bin/triangle_test


PostBuild.window_test.Release:
/Users/mac/my\ mac/graphics.com391/Labs/lab06/build/bin/window_test:
	/bin/rm -f /Users/mac/my\ mac/graphics.com391/Labs/lab06/build/bin/window_test


PostBuild.geometry_test.MinSizeRel:
/Users/mac/my\ mac/graphics.com391/Labs/lab06/build/bin/geometry_test:
	/bin/rm -f /Users/mac/my\ mac/graphics.com391/Labs/lab06/build/bin/geometry_test


PostBuild.lightning_test.MinSizeRel:
/Users/mac/my\ mac/graphics.com391/Labs/lab06/build/bin/lightning_test:
	/bin/rm -f /Users/mac/my\ mac/graphics.com391/Labs/lab06/build/bin/lightning_test


PostBuild.scene_graph_test.MinSizeRel:
/Users/mac/my\ mac/graphics.com391/Labs/lab06/build/bin/scene_graph_test:
	/bin/rm -f /Users/mac/my\ mac/graphics.com391/Labs/lab06/build/bin/scene_graph_test


PostBuild.triangle_test.MinSizeRel:
/Users/mac/my\ mac/graphics.com391/Labs/lab06/build/bin/triangle_test:
	/bin/rm -f /Users/mac/my\ mac/graphics.com391/Labs/lab06/build/bin/triangle_test


PostBuild.window_test.MinSizeRel:
/Users/mac/my\ mac/graphics.com391/Labs/lab06/build/bin/window_test:
	/bin/rm -f /Users/mac/my\ mac/graphics.com391/Labs/lab06/build/bin/window_test


PostBuild.geometry_test.RelWithDebInfo:
/Users/mac/my\ mac/graphics.com391/Labs/lab06/build/bin/geometry_test:
	/bin/rm -f /Users/mac/my\ mac/graphics.com391/Labs/lab06/build/bin/geometry_test


PostBuild.lightning_test.RelWithDebInfo:
/Users/mac/my\ mac/graphics.com391/Labs/lab06/build/bin/lightning_test:
	/bin/rm -f /Users/mac/my\ mac/graphics.com391/Labs/lab06/build/bin/lightning_test


PostBuild.scene_graph_test.RelWithDebInfo:
/Users/mac/my\ mac/graphics.com391/Labs/lab06/build/bin/scene_graph_test:
	/bin/rm -f /Users/mac/my\ mac/graphics.com391/Labs/lab06/build/bin/scene_graph_test


PostBuild.triangle_test.RelWithDebInfo:
/Users/mac/my\ mac/graphics.com391/Labs/lab06/build/bin/triangle_test:
	/bin/rm -f /Users/mac/my\ mac/graphics.com391/Labs/lab06/build/bin/triangle_test


PostBuild.window_test.RelWithDebInfo:
/Users/mac/my\ mac/graphics.com391/Labs/lab06/build/bin/window_test:
	/bin/rm -f /Users/mac/my\ mac/graphics.com391/Labs/lab06/build/bin/window_test




# For each target create a dummy ruleso the target does not have to exist

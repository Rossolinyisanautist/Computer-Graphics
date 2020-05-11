# DO NOT EDIT
# This makefile makes sure all linkable targets are
# up-to-date with anything they link to
default:
	echo "Do not invoke directly"

# Rules to remove targets that are older than anything to which they
# link.  This forces Xcode to relink the targets from scratch.  It
# does not seem to check these dependencies itself.
PostBuild.material_properties_test.Debug:
/Users/mac/my\ mac/graphics.com391/Labs/lab08/build/bin/material_properties_test:
	/bin/rm -f /Users/mac/my\ mac/graphics.com391/Labs/lab08/build/bin/material_properties_test


PostBuild.textured_plane_test.Debug:
/Users/mac/my\ mac/graphics.com391/Labs/lab08/build/bin/textured_plane_test:
	/bin/rm -f /Users/mac/my\ mac/graphics.com391/Labs/lab08/build/bin/textured_plane_test


PostBuild.window_test.Debug:
/Users/mac/my\ mac/graphics.com391/Labs/lab08/build/bin/window_test:
	/bin/rm -f /Users/mac/my\ mac/graphics.com391/Labs/lab08/build/bin/window_test


PostBuild.material_properties_test.Release:
/Users/mac/my\ mac/graphics.com391/Labs/lab08/build/bin/material_properties_test:
	/bin/rm -f /Users/mac/my\ mac/graphics.com391/Labs/lab08/build/bin/material_properties_test


PostBuild.textured_plane_test.Release:
/Users/mac/my\ mac/graphics.com391/Labs/lab08/build/bin/textured_plane_test:
	/bin/rm -f /Users/mac/my\ mac/graphics.com391/Labs/lab08/build/bin/textured_plane_test


PostBuild.window_test.Release:
/Users/mac/my\ mac/graphics.com391/Labs/lab08/build/bin/window_test:
	/bin/rm -f /Users/mac/my\ mac/graphics.com391/Labs/lab08/build/bin/window_test


PostBuild.material_properties_test.MinSizeRel:
/Users/mac/my\ mac/graphics.com391/Labs/lab08/build/bin/material_properties_test:
	/bin/rm -f /Users/mac/my\ mac/graphics.com391/Labs/lab08/build/bin/material_properties_test


PostBuild.textured_plane_test.MinSizeRel:
/Users/mac/my\ mac/graphics.com391/Labs/lab08/build/bin/textured_plane_test:
	/bin/rm -f /Users/mac/my\ mac/graphics.com391/Labs/lab08/build/bin/textured_plane_test


PostBuild.window_test.MinSizeRel:
/Users/mac/my\ mac/graphics.com391/Labs/lab08/build/bin/window_test:
	/bin/rm -f /Users/mac/my\ mac/graphics.com391/Labs/lab08/build/bin/window_test


PostBuild.material_properties_test.RelWithDebInfo:
/Users/mac/my\ mac/graphics.com391/Labs/lab08/build/bin/material_properties_test:
	/bin/rm -f /Users/mac/my\ mac/graphics.com391/Labs/lab08/build/bin/material_properties_test


PostBuild.textured_plane_test.RelWithDebInfo:
/Users/mac/my\ mac/graphics.com391/Labs/lab08/build/bin/textured_plane_test:
	/bin/rm -f /Users/mac/my\ mac/graphics.com391/Labs/lab08/build/bin/textured_plane_test


PostBuild.window_test.RelWithDebInfo:
/Users/mac/my\ mac/graphics.com391/Labs/lab08/build/bin/window_test:
	/bin/rm -f /Users/mac/my\ mac/graphics.com391/Labs/lab08/build/bin/window_test




# For each target create a dummy ruleso the target does not have to exist

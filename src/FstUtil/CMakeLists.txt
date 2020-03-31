ROOT_GENERATE_DICTIONARY(G__FstRawHit
  ${CMAKE_CURRENT_SOURCE_DIR}/FstRawHit.h
  ${CMAKE_CURRENT_SOURCE_DIR}/FstCons.h
  LINKDEF ${CMAKE_CURRENT_SOURCE_DIR}/FstRawHitLinkDef.h)

add_library(FstRawHit SHARED FstRawHit.cxx G__FstRawHit.cxx)
target_link_libraries(FstRawHit ${ROOT_LIBRARIES})

install(TARGETS FstRawHit DESTINATION lib)
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/libFstRawHit_rdict.pcm" DESTINATION lib)
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/libFstRawHit.rootmap" DESTINATION lib)

ROOT_GENERATE_DICTIONARY(G__FstCluster
  ${CMAKE_CURRENT_SOURCE_DIR}/FstCluster.h
  ${CMAKE_CURRENT_SOURCE_DIR}/FstCons.h
  ${CMAKE_CURRENT_SOURCE_DIR}/FstRawHit.h
  LINKDEF ${CMAKE_CURRENT_SOURCE_DIR}/FstClusterLinkDef.h)

add_library(FstCluster SHARED FstCluster.cxx ${CMAKE_CURRENT_SOURCE_DIR}/FstRawHit.cxx G__FstCluster.cxx)
target_link_libraries(FstCluster ${ROOT_LIBRARIES})

install(TARGETS FstCluster DESTINATION lib)
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/libFstCluster_rdict.pcm" DESTINATION lib)
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/libFstCluster.rootmap" DESTINATION lib)

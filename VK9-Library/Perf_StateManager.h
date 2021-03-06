/*
Copyright(c) 2018 Christopher Joseph Dean Schaefer

This software is provided 'as-is', without any express or implied
warranty.In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions :

1. The origin of this software must not be misrepresented; you must not
claim that you wrote the original software.If you use this software
in a product, an acknowledgment in the product documentation would be
appreciated but is not required.
2. Altered source versions must be plainly marked as such, and must not be
misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.
*/

#include <atomic>
#include <memory>
#include <vector>
#include <chrono>
#include <boost/container/flat_map.hpp>
#include <boost/container/small_vector.hpp>
#include <vulkan/vulkan.hpp>
#include <vulkan/vk_sdk_platform.h>
#include <Eigen/Dense>

#include "Utilities.h"
#include "CTypes.h"

#include "ShaderConverter.h"

#ifdef _DEBUG
#include "renderdoc_app.h"
#endif // _DEBUG

#ifndef STATEMANAGER_H
#define STATEMANAGER_H

#define CACHE_SECONDS 1

VKAPI_ATTR VkBool32 VKAPI_CALL DebugReportCallback(VkDebugReportFlagsEXT flags, VkDebugReportObjectTypeEXT objectType, uint64_t object, size_t location, int32_t messageCode, const char* layerPrefix, const char* message, void* userData);

static PFN_vkCmdPushDescriptorSetKHR pfn_vkCmdPushDescriptorSetKHR;
VKAPI_ATTR void VKAPI_CALL vkCmdPushDescriptorSetKHR(
	VkCommandBuffer                             commandBuffer,
	VkPipelineBindPoint                         pipelineBindPoint,
	VkPipelineLayout                            layout,
	uint32_t                                    set,
	uint32_t                                    descriptorWriteCount,
	const VkWriteDescriptorSet*                 pDescriptorWrites);

static PFN_vkCreateDebugReportCallbackEXT pfn_vkCreateDebugReportCallbackEXT;
VKAPI_ATTR VkResult VKAPI_CALL vkCreateDebugReportCallbackEXT(
	VkInstance                                  instance,
	const VkDebugReportCallbackCreateInfoEXT*   pCreateInfo,
	const VkAllocationCallbacks*                pAllocator,
	VkDebugReportCallbackEXT*                   pCallback);

static PFN_vkDestroyDebugReportCallbackEXT pfn_vkDestroyDebugReportCallbackEXT;
VKAPI_ATTR void VKAPI_CALL vkDestroyDebugReportCallbackEXT(
	VkInstance                                  instance,
	VkDebugReportCallbackEXT                    callback,
	const VkAllocationCallbacks*                pAllocator);

static PFN_vkDebugReportMessageEXT pfn_vkDebugReportMessageEXT;
VKAPI_ATTR void VKAPI_CALL vkDebugReportMessageEXT(
	VkInstance                                  instance,
	VkDebugReportFlagsEXT                       flags,
	VkDebugReportObjectTypeEXT                  objectType,
	uint64_t                                    object,
	size_t                                      location,
	int32_t                                     messageCode,
	const char*                                 pLayerPrefix,
	const char*                                 pMessage);

#include "RealDevice.h"
#include "RealInstance.h"
#include "RealWindow.h"
#include "RealTexture.h"
#include "RealSurface.h"
#include "RealVertexBuffer.h"
#include "RealIndexBuffer.h"
#include "SamplerRequest.h"
#include "ResourceContext.h"
#include "DrawContext.h"

struct StateManager
{
	boost::container::small_vector< std::shared_ptr<RealInstance>, 1> mInstances;
	std::atomic_size_t mInstanceKey = 0;

	boost::container::small_vector< std::shared_ptr<RealWindow>, 1> mWindows;
	std::atomic_size_t mWindowsKey = 0;

	std::vector< std::shared_ptr<RealVertexBuffer> > mVertexBuffers;
	std::atomic_size_t mVertexBufferKey = 0;

	std::vector< std::shared_ptr<RealIndexBuffer> > mIndexBuffers;
	std::atomic_size_t mIndexBufferKey = 0;

	std::vector< std::shared_ptr<RealTexture> > mTextures;
	std::atomic_size_t mTextureKey = 0;

	std::vector< std::shared_ptr<RealSurface> > mSurfaces;
	std::atomic_size_t mSurfaceKey = 0;

	std::vector< std::shared_ptr<ShaderConverter> > mShaderConverters;
	std::atomic_size_t mShaderConverterKey = 0;

	StateManager();
	~StateManager();

	void DestroyWindow(size_t id);
	void CreateWindow1(size_t id, void* argument1, void* argument2);

	void DestroyInstance(size_t id);
	void CreateInstance();

	void DestroyVertexBuffer(size_t id);
	void CreateVertexBuffer(size_t id, void* argument1);

	void DestroyIndexBuffer(size_t id);
	void CreateIndexBuffer(size_t id, void* argument1);

	void DestroyTexture(size_t id);
	void CreateTexture(size_t id, void* argument1);

	void DestroyCubeTexture(size_t id);
	void CreateCubeTexture(size_t id, void* argument1);

	void DestroyVolumeTexture(size_t id);
	void CreateVolumeTexture(size_t id, void* argument1);

	void DestroySurface(size_t id);
	void CreateSurface(size_t id, void* argument1);

	void DestroyVolume(size_t id);
	void CreateVolume(size_t id, void* argument1);

	void DestroyShader(size_t id);
	void CreateShader(size_t id, void* argument1, void* argument2, void* argument3);

};

#endif // STATEMANAGER_H
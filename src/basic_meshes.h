#ifndef GROTA_BASIC_MESHES_H
#define GROTA_BASIC_MESHES_H
#include "denise.hpp"
using namespace Denise;

float quad_vertices[] = {
	// positions      // texture coords
	-0.5f,  0.5f,0.0f  , 0.0f,  0.0f,1.0f  , 0.0f, 1.0f, // top left 
	 0.5f, -0.5f,0.0f  , 0.0f,  0.0f,1.0f  , 1.0f, 0.0f, // bottom right
	 0.5f,  0.5f,0.0f  , 0.0f,  0.0f,1.0f  , 1.0f, 1.0f, // top right

	-0.5f,  0.5f,0.0f  , 0.0f,  0.0f,1.0f  , 0.0f, 1.0f,  // top left 
	-0.5f, -0.5f,0.0f  , 0.0f,  0.0f,1.0f  , 0.0f, 0.0f, // bottom left
         0.5f, -0.5f,0.0f  , 0.0f,  0.0f,1.0f  , 1.0f, 0.0f // bottom right
};

float box_vertices[] = {
	// positions      // texture coords
		-0.5f,-0.5f,-0.5f,-0.5f,-0.5f,-0.5f, 0.000059f, 1.f-0.000004f, 
		-0.5f,-0.5f, 0.5f,-0.5f,-0.5f, 0.5f, 0.000103f, 1.f-0.336048f, 
		-0.5f, 0.5f, 0.5f,-0.5f, 0.5f, 0.5f, 0.335973f, 1.f-0.335903f, 
        
		 0.5f, 0.5f,-0.5f, 0.5f, 0.5f,-0.5f, 1.000023f, 1.f-0.000013f, 
		-0.5f,-0.5f,-0.5f,-0.5f,-0.5f,-0.5f, 0.667979f, 1.f-0.335851f, 
		-0.5f, 0.5f,-0.5f,-0.5f, 0.5f,-0.5f, 0.999958f, 1.f-0.336064f, 
		 0.5f,-0.5f, 0.5f, 0.5f,-0.5f, 0.5f, 0.667979f, 1.f-0.335851f, 
		-0.5f,-0.5f,-0.5f,-0.5f,-0.5f,-0.5f, 0.336024f, 1.f-0.671877f, 
		 0.5f,-0.5f,-0.5f, 0.5f,-0.5f,-0.5f, 0.667969f, 1.f-0.671889f, 
		 0.5f, 0.5f,-0.5f, 0.5f, 0.5f,-0.5f, 1.000023f, 1.f-0.000013f, 
		 0.5f,-0.5f,-0.5f, 0.5f,-0.5f,-0.5f, 0.668104f, 1.f-0.000013f, 
		-0.5f,-0.5f,-0.5f,-0.5f,-0.5f,-0.5f, 0.667979f, 1.f-0.335851f, 
		-0.5f,-0.5f,-0.5f,-0.5f,-0.5f,-0.5f, 0.000059f, 1.f-0.000004f, 
		-0.5f, 0.5f, 0.5f,-0.5f, 0.5f, 0.5f, 0.335973f, 1.f-0.335903f, 
		-0.5f, 0.5f,-0.5f,-0.5f, 0.5f,-0.5f, 0.336098f, 1.f-0.000071f, 
		 0.5f,-0.5f, 0.5f, 0.5f,-0.5f, 0.5f, 0.667979f, 1.f-0.335851f, 
		-0.5f,-0.5f, 0.5f,-0.5f,-0.5f, 0.5f, 0.335973f, 1.f-0.335903f, 
		-0.5f,-0.5f,-0.5f,-0.5f,-0.5f,-0.5f, 0.336024f, 1.f-0.671877f, 
		-0.5f, 0.5f, 0.5f,-0.5f, 0.5f, 0.5f, 1.000004f, 1.f-0.671847f, 
		-0.5f,-0.5f, 0.5f,-0.5f,-0.5f, 0.5f, 0.999958f, 1.f-0.336064f, 
		 0.5f,-0.5f, 0.5f, 0.5f,-0.5f, 0.5f, 0.667979f, 1.f-0.335851f, 
		 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.668104f, 1.f-0.000013f, 
		 0.5f,-0.5f,-0.5f, 0.5f,-0.5f,-0.5f, 0.335973f, 1.f-0.335903f, 
		 0.5f, 0.5f,-0.5f, 0.5f, 0.5f,-0.5f, 0.667979f, 1.f-0.335851f, 
		 0.5f,-0.5f,-0.5f, 0.5f,-0.5f,-0.5f, 0.335973f, 1.f-0.335903f, 
		 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.668104f, 1.f-0.000013f, 
		 0.5f,-0.5f, 0.5f, 0.5f,-0.5f, 0.5f, 0.336098f, 1.f-0.000071f, 
		 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.000103f, 1.f-0.336048f, 
		 0.5f, 0.5f,-0.5f, 0.5f, 0.5f,-0.5f, 0.000004f, 1.f-0.671870f, 
		-0.5f, 0.5f,-0.5f,-0.5f, 0.5f,-0.5f, 0.336024f, 1.f-0.671877f, 
		 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.000103f, 1.f-0.336048f, 
		-0.5f, 0.5f,-0.5f,-0.5f, 0.5f,-0.5f, 0.336024f, 1.f-0.671877f, 
		-0.5f, 0.5f, 0.5f,-0.5f, 0.5f, 0.5f, 0.335973f, 1.f-0.335903f, 
		 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.667969f, 1.f-0.671889f, 
		-0.5f, 0.5f, 0.5f,-0.5f, 0.5f, 0.5f, 1.000004f, 1.f-0.671847f, 
		 0.5f,-0.5f, 0.5f, 0.5f,-0.5f, 0.5 ,0.667979f,  1.f-0.335851f
}; 

float sphere_vertices[]={
        0.000000,-1.000000,0.000000,-0.000000,-1.000000,-0.000000,0.000154,0.000154,
        0.425323,-0.850654,0.309011,0.425300,-0.850700,0.309000,0.073643,0.073643,
        -0.162456,-0.850654,0.499995,-0.162500,-0.850700,0.500000,0.095325,0.095325,
        0.723607,-0.447220,0.525725,0.723600,-0.447200,0.525700,0.114561,0.114561,
        0.425323,-0.850654,0.309011,0.425300,-0.850700,0.309000,0.047454,0.047454,
        0.850648,-0.525736,0.000000,0.850600,-0.525700,0.000000,0.156980,0.156980,
        0.000000,-1.000000,0.000000,-0.000000,-1.000000,-0.000000,0.009138,0.009138,
        -0.162456,-0.850654,0.499995,-0.162500,-0.850700,0.500000,0.091343,0.091343,
        -0.525730,-0.850652,0.000000,-0.525700,-0.850700,-0.000000,0.094968,0.094968,
        0.000000,-1.000000,0.000000,-0.000000,-1.000000,-0.000000,0.009138,0.009138,
        -0.525730,-0.850652,0.000000,-0.525700,-0.850700,-0.000000,0.094968,0.094968,
        -0.162456,-0.850654,-0.499995,-0.162500,-0.850700,-0.500000,0.000154,0.000154,
        0.000000,-1.000000,0.000000,-0.000000,-1.000000,-0.000000,0.470208,0.470208,
        -0.162456,-0.850654,-0.499995,-0.162500,-0.850700,-0.500000,0.565379,0.565379,
        0.425323,-0.850654,-0.309011,0.425300,-0.850700,-0.309000,0.543696,0.543696,
        0.723607,-0.447220,0.525725,0.723600,-0.447200,0.525700,0.114561,0.114561,
        0.850648,-0.525736,0.000000,0.850600,-0.525700,0.000000,0.156980,0.156980,
        0.951058,0.000000,0.309013,0.951100,-0.000000,0.309000,0.210030,0.210030,
        -0.276388,-0.447220,0.850649,-0.276400,-0.447200,0.850600,0.191577,0.191577,
        0.262869,-0.525738,0.809012,0.262900,-0.525700,0.809000,0.175152,0.175152,
        0.000000,0.000000,1.000000,0.000000,-0.000000,1.000000,0.264973,0.264973,
        -0.894426,-0.447216,0.000000,-0.894400,-0.447200,0.000000,0.173444,0.173444,
        -0.688189,-0.525736,0.499997,-0.688200,-0.525700,0.500000,0.193001,0.193001,
        -0.951058,0.000000,0.309013,-0.951100,0.000000,0.309000,0.260024,0.260024,
        -0.276388,-0.447220,-0.850649,-0.276400,-0.447200,-0.850600,0.661631,0.661631,
        -0.688189,-0.525736,-0.499997,-0.688200,-0.525700,-0.500000,0.623764,0.623764,
        -0.587786,0.000000,-0.809017,-0.587800,-0.000000,-0.809000,0.737872,0.737872,
        0.723607,-0.447220,-0.525725,0.723600,-0.447200,-0.525700,0.632233,0.632233,
        0.262869,-0.525738,-0.809012,0.262900,-0.525700,-0.809000,0.645206,0.645206,
        0.587786,0.000000,-0.809017,0.587800,0.000000,-0.809000,0.732182,0.732182,
        0.723607,-0.447220,0.525725,0.723600,-0.447200,0.525700,0.114561,0.114561,
        0.951058,0.000000,0.309013,0.951100,-0.000000,0.309000,0.210030,0.210030,
        0.587786,0.000000,0.809017,0.587800,0.000000,0.809000,0.159874,0.159874,
        -0.276388,-0.447220,0.850649,-0.276400,-0.447200,0.850600,0.191577,0.191577,
        0.000000,0.000000,1.000000,0.000000,-0.000000,1.000000,0.264973,0.264973,
        -0.587786,0.000000,0.809017,-0.587800,-0.000000,0.809000,0.267818,0.267818,
        -0.894426,-0.447216,0.000000,-0.894400,-0.447200,0.000000,0.173444,0.173444,
        -0.951058,0.000000,0.309013,-0.951100,0.000000,0.309000,0.260024,0.260024,
        -0.951058,0.000000,-0.309013,-0.951100,0.000000,-0.309000,0.212964,0.212964,
        -0.276388,-0.447220,-0.850649,-0.276400,-0.447200,-0.850600,0.661631,0.661631,
        -0.587786,0.000000,-0.809017,-0.587800,-0.000000,-0.809000,0.737872,0.737872,
        0.000000,0.000000,-1.000000,0.000000,0.000000,-1.000000,0.735027,0.735027,
        0.723607,-0.447220,-0.525725,0.723600,-0.447200,-0.525700,0.206976,0.206976,
        0.587786,0.000000,-0.809017,0.587800,0.000000,-0.809000,0.310331,0.310331,
        0.951058,0.000000,-0.309013,0.951100,-0.000000,-0.309000,0.257090,0.257090,
        0.276388,0.447220,0.850649,0.276400,0.447200,0.850600,0.338369,0.338369,
        0.688189,0.525736,0.499997,0.688200,0.525700,0.500000,0.376236,0.376236,
        0.162456,0.850654,0.499995,0.162500,0.850700,0.500000,0.434621,0.434621,
        -0.723607,0.447220,0.525725,-0.723600,0.447200,0.525700,0.367767,0.367767,
        -0.262869,0.525738,0.809012,-0.262900,0.525700,0.809000,0.354794,0.354794,
        -0.425323,0.850654,0.309011,-0.425300,0.850700,0.309000,0.456304,0.456304,
        -0.723607,0.447220,-0.525725,-0.723600,0.447200,-0.525700,0.263078,0.263078,
        -0.850648,0.525736,0.000000,-0.850600,0.525700,-0.000000,0.313074,0.313074,
        -0.425323,0.850654,-0.309011,-0.425300,0.850700,-0.309000,0.366419,0.366419,
        0.276388,0.447220,-0.850649,0.276400,0.447200,-0.850600,0.808423,0.808423,
        -0.262869,0.525738,-0.809012,-0.262900,0.525700,-0.809000,0.824848,0.824848,
        0.162456,0.850654,-0.499995,0.162500,0.850700,-0.500000,0.904675,0.904675,
        0.894426,0.447216,0.000000,0.894400,0.447200,0.000000,0.296610,0.296610,
        0.688189,0.525736,-0.499997,0.688200,0.525700,-0.500000,0.364910,0.364910,
        0.525730,0.850652,0.000000,0.525700,0.850700,-0.000000,0.375086,0.375086,
        0.525730,0.850652,0.000000,0.525700,0.850700,-0.000000,0.375086,0.375086,
        0.162456,0.850654,-0.499995,0.162500,0.850700,-0.500000,0.469900,0.469900,
        0.000000,1.000000,0.000000,0.000000,1.000000,-0.000000,0.460915,0.460915,
        0.525730,0.850652,0.000000,0.525700,0.850700,-0.000000,0.375086,0.375086,
        0.688189,0.525736,-0.499997,0.688200,0.525700,-0.500000,0.364910,0.364910,
        0.162456,0.850654,-0.499995,0.162500,0.850700,-0.500000,0.469900,0.469900,
        0.688189,0.525736,-0.499997,0.688200,0.525700,-0.500000,0.846290,0.846290,
        0.276388,0.447220,-0.850649,0.276400,0.447200,-0.850600,0.808423,0.808423,
        0.162456,0.850654,-0.499995,0.162500,0.850700,-0.500000,0.904675,0.904675,
        0.162456,0.850654,-0.499995,0.162500,0.850700,-0.500000,0.904675,0.904675,
        -0.425323,0.850654,-0.309011,-0.425300,0.850700,-0.309000,0.926358,0.926358,
        0.000000,1.000000,0.000000,0.000000,1.000000,-0.000000,0.999846,0.999846,
        0.162456,0.850654,-0.499995,0.162500,0.850700,-0.500000,0.904675,0.904675,
        -0.262869,0.525738,-0.809012,-0.262900,0.525700,-0.809000,0.824848,0.824848,
        -0.425323,0.850654,-0.309011,-0.425300,0.850700,-0.309000,0.926358,0.926358,
        -0.262869,0.525738,-0.809012,-0.262900,0.525700,-0.809000,0.824848,0.824848,
        -0.723607,0.447220,-0.525725,-0.723600,0.447200,-0.525700,0.837821,0.837821,
        -0.425323,0.850654,-0.309011,-0.425300,0.850700,-0.309000,0.926358,0.926358,
        -0.425323,0.850654,-0.309011,-0.425300,0.850700,-0.309000,0.366419,0.366419,
        -0.425323,0.850654,0.309011,-0.425300,0.850700,0.309000,0.422599,0.422599,
        0.000000,1.000000,0.000000,0.000000,1.000000,-0.000000,0.469900,0.469900,
        -0.425323,0.850654,-0.309011,-0.425300,0.850700,-0.309000,0.366419,0.366419,
        -0.850648,0.525736,0.000000,-0.850600,0.525700,-0.000000,0.313074,0.313074,
        -0.425323,0.850654,0.309011,-0.425300,0.850700,0.309000,0.422599,0.422599,
        -0.850648,0.525736,0.000000,-0.850600,0.525700,-0.000000,0.313074,0.313074,
        -0.723607,0.447220,0.525725,-0.723600,0.447200,0.525700,0.355493,0.355493,
        -0.425323,0.850654,0.309011,-0.425300,0.850700,0.309000,0.422599,0.422599,
        -0.425323,0.850654,0.309011,-0.425300,0.850700,0.309000,0.456304,0.456304,
        0.162456,0.850654,0.499995,0.162500,0.850700,0.500000,0.434621,0.434621,
        0.000000,1.000000,0.000000,0.000000,1.000000,-0.000000,0.529792,0.529792,
        -0.425323,0.850654,0.309011,-0.425300,0.850700,0.309000,0.456304,0.456304,
        -0.262869,0.525738,0.809012,-0.262900,0.525700,0.809000,0.354794,0.354794,
        0.162456,0.850654,0.499995,0.162500,0.850700,0.500000,0.434621,0.434621,
        -0.262869,0.525738,0.809012,-0.262900,0.525700,0.809000,0.354794,0.354794,
        0.276388,0.447220,0.850649,0.276400,0.447200,0.850600,0.338369,0.338369,
        0.162456,0.850654,0.499995,0.162500,0.850700,0.500000,0.434621,0.434621,
        0.162456,0.850654,0.499995,0.162500,0.850700,0.500000,0.378710,0.378710,
        0.525730,0.850652,0.000000,0.525700,0.850700,-0.000000,0.375086,0.375086,
        0.000000,1.000000,0.000000,0.000000,1.000000,-0.000000,0.460915,0.460915,
        0.162456,0.850654,0.499995,0.162500,0.850700,0.500000,0.378710,0.378710,
        0.688189,0.525736,0.499997,0.688200,0.525700,0.500000,0.277053,0.277053,
        0.525730,0.850652,0.000000,0.525700,0.850700,-0.000000,0.375086,0.375086,
        0.688189,0.525736,0.499997,0.688200,0.525700,0.500000,0.277053,0.277053,
        0.894426,0.447216,0.000000,0.894400,0.447200,0.000000,0.296610,0.296610,
        0.525730,0.850652,0.000000,0.525700,0.850700,-0.000000,0.375086,0.375086,
        0.951058,0.000000,-0.309013,0.951100,-0.000000,-0.309000,0.257090,0.257090,
        0.688189,0.525736,-0.499997,0.688200,0.525700,-0.500000,0.364910,0.364910,
        0.894426,0.447216,0.000000,0.894400,0.447200,0.000000,0.296610,0.296610,
        0.951058,0.000000,-0.309013,0.951100,-0.000000,-0.309000,0.257090,0.257090,
        0.587786,0.000000,-0.809017,0.587800,0.000000,-0.809000,0.310331,0.310331,
        0.688189,0.525736,-0.499997,0.688200,0.525700,-0.500000,0.364910,0.364910,
        0.587786,0.000000,-0.809017,0.587800,0.000000,-0.809000,0.732182,0.732182,
        0.276388,0.447220,-0.850649,0.276400,0.447200,-0.850600,0.808423,0.808423,
        0.688189,0.525736,-0.499997,0.688200,0.525700,-0.500000,0.846290,0.846290,
        0.000000,0.000000,-1.000000,0.000000,0.000000,-1.000000,0.735027,0.735027,
        -0.262869,0.525738,-0.809012,-0.262900,0.525700,-0.809000,0.824848,0.824848,
        0.276388,0.447220,-0.850649,0.276400,0.447200,-0.850600,0.808423,0.808423,
        0.000000,0.000000,-1.000000,0.000000,0.000000,-1.000000,0.735027,0.735027,
        -0.587786,0.000000,-0.809017,-0.587800,-0.000000,-0.809000,0.737872,0.737872,
        -0.262869,0.525738,-0.809012,-0.262900,0.525700,-0.809000,0.824848,0.824848,
        -0.587786,0.000000,-0.809017,-0.587800,-0.000000,-0.809000,0.737872,0.737872,
        -0.723607,0.447220,-0.525725,-0.723600,0.447200,-0.525700,0.837821,0.837821,
        -0.262869,0.525738,-0.809012,-0.262900,0.525700,-0.809000,0.824848,0.824848,
        -0.951058,0.000000,-0.309013,-0.951100,0.000000,-0.309000,0.212964,0.212964,
        -0.850648,0.525736,0.000000,-0.850600,0.525700,-0.000000,0.313074,0.313074,
        -0.723607,0.447220,-0.525725,-0.723600,0.447200,-0.525700,0.263078,0.263078,
        -0.951058,0.000000,-0.309013,-0.951100,0.000000,-0.309000,0.212964,0.212964,
        -0.951058,0.000000,0.309013,-0.951100,0.000000,0.309000,0.260024,0.260024,
        -0.850648,0.525736,0.000000,-0.850600,0.525700,-0.000000,0.313074,0.313074,
        -0.951058,0.000000,0.309013,-0.951100,0.000000,0.309000,0.260024,0.260024,
        -0.723607,0.447220,0.525725,-0.723600,0.447200,0.525700,0.355493,0.355493,
        -0.850648,0.525736,0.000000,-0.850600,0.525700,-0.000000,0.313074,0.313074,
        -0.587786,0.000000,0.809017,-0.587800,-0.000000,0.809000,0.267818,0.267818,
        -0.262869,0.525738,0.809012,-0.262900,0.525700,0.809000,0.354794,0.354794,
        -0.723607,0.447220,0.525725,-0.723600,0.447200,0.525700,0.367767,0.367767,
        -0.587786,0.000000,0.809017,-0.587800,-0.000000,0.809000,0.267818,0.267818,
        0.000000,0.000000,1.000000,0.000000,-0.000000,1.000000,0.264973,0.264973,
        -0.262869,0.525738,0.809012,-0.262900,0.525700,0.809000,0.354794,0.354794,
        0.000000,0.000000,1.000000,0.000000,-0.000000,1.000000,0.264973,0.264973,
        0.276388,0.447220,0.850649,0.276400,0.447200,0.850600,0.338369,0.338369,
        -0.262869,0.525738,0.809012,-0.262900,0.525700,0.809000,0.354794,0.354794,
        0.587786,0.000000,0.809017,0.587800,0.000000,0.809000,0.262129,0.262129,
        0.688189,0.525736,0.499997,0.688200,0.525700,0.500000,0.376236,0.376236,
        0.276388,0.447220,0.850649,0.276400,0.447200,0.850600,0.338369,0.338369,
        0.587786,0.000000,0.809017,0.587800,0.000000,0.809000,0.159874,0.159874,
        0.951058,0.000000,0.309013,0.951100,-0.000000,0.309000,0.210030,0.210030,
        0.688189,0.525736,0.499997,0.688200,0.525700,0.500000,0.277053,0.277053,
        0.951058,0.000000,0.309013,0.951100,-0.000000,0.309000,0.210030,0.210030,
        0.894426,0.447216,0.000000,0.894400,0.447200,0.000000,0.296610,0.296610,
        0.688189,0.525736,0.499997,0.688200,0.525700,0.500000,0.277053,0.277053,
        0.587786,0.000000,-0.809017,0.587800,0.000000,-0.809000,0.732182,0.732182,
        0.000000,0.000000,-1.000000,0.000000,0.000000,-1.000000,0.735027,0.735027,
        0.276388,0.447220,-0.850649,0.276400,0.447200,-0.850600,0.808423,0.808423,
        0.587786,0.000000,-0.809017,0.587800,0.000000,-0.809000,0.732182,0.732182,
        0.262869,-0.525738,-0.809012,0.262900,-0.525700,-0.809000,0.645206,0.645206,
        0.000000,0.000000,-1.000000,0.000000,0.000000,-1.000000,0.735027,0.735027,
        0.262869,-0.525738,-0.809012,0.262900,-0.525700,-0.809000,0.645206,0.645206,
        -0.276388,-0.447220,-0.850649,-0.276400,-0.447200,-0.850600,0.661631,0.661631,
        0.000000,0.000000,-1.000000,0.000000,0.000000,-1.000000,0.735027,0.735027,
        -0.587786,0.000000,-0.809017,-0.587800,-0.000000,-0.809000,0.159723,0.159723,
        -0.951058,0.000000,-0.309013,-0.951100,0.000000,-0.309000,0.212964,0.212964,
        -0.723607,0.447220,-0.525725,-0.723600,0.447200,-0.525700,0.263078,0.263078,
        -0.587786,0.000000,-0.809017,-0.587800,-0.000000,-0.809000,0.159723,0.159723,
        -0.688189,-0.525736,-0.499997,-0.688200,-0.525700,-0.500000,0.105144,0.105144,
        -0.951058,0.000000,-0.309013,-0.951100,0.000000,-0.309000,0.212964,0.212964,
        -0.688189,-0.525736,-0.499997,-0.688200,-0.525700,-0.500000,0.105144,0.105144,
        -0.894426,-0.447216,0.000000,-0.894400,-0.447200,0.000000,0.173444,0.173444,
        -0.951058,0.000000,-0.309013,-0.951100,0.000000,-0.309000,0.212964,0.212964,
        -0.951058,0.000000,0.309013,-0.951100,0.000000,0.309000,0.260024,0.260024,
        -0.587786,0.000000,0.809017,-0.587800,-0.000000,0.809000,0.310180,0.310180,
        -0.723607,0.447220,0.525725,-0.723600,0.447200,0.525700,0.355493,0.355493,
        -0.951058,0.000000,0.309013,-0.951100,0.000000,0.309000,0.260024,0.260024,
        -0.688189,-0.525736,0.499997,-0.688200,-0.525700,0.500000,0.193001,0.193001,
        -0.587786,0.000000,0.809017,-0.587800,-0.000000,0.809000,0.310180,0.310180,
        -0.688189,-0.525736,0.499997,-0.688200,-0.525700,0.500000,0.153710,0.153710,
        -0.276388,-0.447220,0.850649,-0.276400,-0.447200,0.850600,0.191577,0.191577,
        -0.587786,0.000000,0.809017,-0.587800,-0.000000,0.809000,0.267818,0.267818,
        0.000000,0.000000,1.000000,0.000000,-0.000000,1.000000,0.264973,0.264973,
        0.587786,0.000000,0.809017,0.587800,0.000000,0.809000,0.262129,0.262129,
        0.276388,0.447220,0.850649,0.276400,0.447200,0.850600,0.338369,0.338369,
        0.000000,0.000000,1.000000,0.000000,-0.000000,1.000000,0.264973,0.264973,
        0.262869,-0.525738,0.809012,0.262900,-0.525700,0.809000,0.175152,0.175152,
        0.587786,0.000000,0.809017,0.587800,0.000000,0.809000,0.262129,0.262129,
        0.262869,-0.525738,0.809012,0.262900,-0.525700,0.809000,0.175152,0.175152,
        0.723607,-0.447220,0.525725,0.723600,-0.447200,0.525700,0.162180,0.162180,
        0.587786,0.000000,0.809017,0.587800,0.000000,0.809000,0.262129,0.262129,
        0.951058,0.000000,0.309013,0.951100,-0.000000,0.309000,0.210030,0.210030,
        0.951058,0.000000,-0.309013,0.951100,-0.000000,-0.309000,0.257090,0.257090,
        0.894426,0.447216,0.000000,0.894400,0.447200,0.000000,0.296610,0.296610,
        0.951058,0.000000,0.309013,0.951100,-0.000000,0.309000,0.210030,0.210030,
        0.850648,-0.525736,0.000000,0.850600,-0.525700,0.000000,0.156980,0.156980,
        0.951058,0.000000,-0.309013,0.951100,-0.000000,-0.309000,0.257090,0.257090,
        0.850648,-0.525736,0.000000,0.850600,-0.525700,0.000000,0.156980,0.156980,
        0.723607,-0.447220,-0.525725,0.723600,-0.447200,-0.525700,0.206976,0.206976,
        0.951058,0.000000,-0.309013,0.951100,-0.000000,-0.309000,0.257090,0.257090,
        0.425323,-0.850654,-0.309011,0.425300,-0.850700,-0.309000,0.543696,0.543696,
        0.262869,-0.525738,-0.809012,0.262900,-0.525700,-0.809000,0.645206,0.645206,
        0.723607,-0.447220,-0.525725,0.723600,-0.447200,-0.525700,0.632233,0.632233,
        0.425323,-0.850654,-0.309011,0.425300,-0.850700,-0.309000,0.543696,0.543696,
        -0.162456,-0.850654,-0.499995,-0.162500,-0.850700,-0.500000,0.565379,0.565379,
        0.262869,-0.525738,-0.809012,0.262900,-0.525700,-0.809000,0.645206,0.645206,
        -0.162456,-0.850654,-0.499995,-0.162500,-0.850700,-0.500000,0.565379,0.565379,
        -0.276388,-0.447220,-0.850649,-0.276400,-0.447200,-0.850600,0.661631,0.661631,
        0.262869,-0.525738,-0.809012,0.262900,-0.525700,-0.809000,0.645206,0.645206,
        -0.162456,-0.850654,-0.499995,-0.162500,-0.850700,-0.500000,0.565379,0.565379,
        -0.688189,-0.525736,-0.499997,-0.688200,-0.525700,-0.500000,0.623764,0.623764,
        -0.276388,-0.447220,-0.850649,-0.276400,-0.447200,-0.850600,0.661631,0.661631,
        -0.162456,-0.850654,-0.499995,-0.162500,-0.850700,-0.500000,0.000154,0.000154,
        -0.525730,-0.850652,0.000000,-0.525700,-0.850700,-0.000000,0.094968,0.094968,
        -0.688189,-0.525736,-0.499997,-0.688200,-0.525700,-0.500000,0.105144,0.105144,
        -0.525730,-0.850652,0.000000,-0.525700,-0.850700,-0.000000,0.094968,0.094968,
        -0.894426,-0.447216,0.000000,-0.894400,-0.447200,0.000000,0.173444,0.173444,
        -0.688189,-0.525736,-0.499997,-0.688200,-0.525700,-0.500000,0.105144,0.105144,
        -0.525730,-0.850652,0.000000,-0.525700,-0.850700,-0.000000,0.094968,0.094968,
        -0.688189,-0.525736,0.499997,-0.688200,-0.525700,0.500000,0.193001,0.193001,
        -0.894426,-0.447216,0.000000,-0.894400,-0.447200,0.000000,0.173444,0.173444,
        -0.525730,-0.850652,0.000000,-0.525700,-0.850700,-0.000000,0.094968,0.094968,
        -0.162456,-0.850654,0.499995,-0.162500,-0.850700,0.500000,0.091343,0.091343,
        -0.688189,-0.525736,0.499997,-0.688200,-0.525700,0.500000,0.193001,0.193001,
        -0.162456,-0.850654,0.499995,-0.162500,-0.850700,0.500000,0.095325,0.095325,
        -0.276388,-0.447220,0.850649,-0.276400,-0.447200,0.850600,0.191577,0.191577,
        -0.688189,-0.525736,0.499997,-0.688200,-0.525700,0.500000,0.153710,0.153710,
        0.850648,-0.525736,0.000000,0.850600,-0.525700,0.000000,0.156980,0.156980,
        0.425323,-0.850654,-0.309011,0.425300,-0.850700,-0.309000,0.103635,0.103635,
        0.723607,-0.447220,-0.525725,0.723600,-0.447200,-0.525700,0.206976,0.206976,
        0.850648,-0.525736,0.000000,0.850600,-0.525700,0.000000,0.156980,0.156980,
        0.425323,-0.850654,0.309011,0.425300,-0.850700,0.309000,0.047454,0.047454,
        0.425323,-0.850654,-0.309011,0.425300,-0.850700,-0.309000,0.103635,0.103635,
        0.425323,-0.850654,0.309011,0.425300,-0.850700,0.309000,0.047454,0.047454,
        0.000000,-1.000000,0.000000,-0.000000,-1.000000,-0.000000,0.000154,0.000154,
        0.425323,-0.850654,-0.309011,0.425300,-0.850700,-0.309000,0.103635,0.103635,
        -0.162456,-0.850654,0.499995,-0.162500,-0.850700,0.500000,0.095325,0.095325,
        0.262869,-0.525738,0.809012,0.262900,-0.525700,0.809000,0.175152,0.175152,
        -0.276388,-0.447220,0.850649,-0.276400,-0.447200,0.850600,0.191577,0.191577,
        -0.162456,-0.850654,0.499995,-0.162500,-0.850700,0.500000,0.095325,0.095325,
        0.425323,-0.850654,0.309011,0.425300,-0.850700,0.309000,0.073643,0.073643,
        0.262869,-0.525738,0.809012,0.262900,-0.525700,0.809000,0.175152,0.175152,
        0.425323,-0.850654,0.309011,0.425300,-0.850700,0.309000,0.073643,0.073643,
        0.723607,-0.447220,0.525725,0.723600,-0.447200,0.525700,0.162180,0.162180,
        0.262869,-0.525738,0.809012,0.262900,-0.525700,0.809000,0.175152,0.175152
};
#endif
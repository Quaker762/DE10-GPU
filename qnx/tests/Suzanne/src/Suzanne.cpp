#include <GL/gl.h>
#include <r3d/rush3d.h>
#include <iostream>
#include <sys/neutrino.h>
#include <cstdlib>
#include <cmath>
#include <vector>

#define VIDEO_WIDTH  800
#define VIDEO_HEIGHT 600

#define NUM_INDICES 2904

static const GLfloat g_vertex_buffer_data[] =
{
		0.875000,0.328125,1.531250,
		-0.875000,0.328125,1.531250,
		1.000000,0.187500,1.375000,
		-1.000000,0.187500,1.375000,
		1.093750,0.109375,1.156250,
		-1.093750,0.109375,1.156250,
		0.703125,-0.046875,1.234375,
		-0.703125,-0.046875,1.234375,
		0.703125,0.062500,1.437500,
		-0.703125,0.062500,1.437500,
		0.703125,0.265625,1.562500,
		-0.703125,0.265625,1.562500,
		0.546875,0.328125,1.593750,
		-0.546875,0.328125,1.593750,
		0.406250,0.187500,1.484375,
		-0.406250,0.187500,1.484375,
		0.312500,0.109375,1.296875,
		-0.312500,0.109375,1.296875,
		0.156250,0.484375,1.312500,
		-0.156250,0.484375,1.312500,
		0.281250,0.484375,1.484375,
		-0.281250,0.484375,1.484375,
		0.484375,0.484375,1.593750,
		-0.484375,0.484375,1.593750,
		0.546875,0.656250,1.593750,
		-0.546875,0.656250,1.593750,
		0.406250,0.781250,1.484375,
		-0.406250,0.781250,1.484375,
		0.312500,0.875000,1.296875,
		-0.312500,0.875000,1.296875,
		0.703125,1.031250,1.234375,
		-0.703125,1.031250,1.234375,
		0.703125,0.906250,1.437500,
		-0.703125,0.906250,1.437500,
		0.703125,0.718750,1.562500,
		-0.703125,0.718750,1.562500,
		0.875000,0.656250,1.531250,
		-0.875000,0.656250,1.531250,
		1.000000,0.781250,1.375000,
		-1.000000,0.781250,1.375000,
		1.093750,0.875000,1.156250,
		-1.093750,0.875000,1.156250,
		1.250000,0.484375,1.125000,
		-1.250000,0.484375,1.125000,
		1.125000,0.484375,1.343750,
		-1.125000,0.484375,1.343750,
		0.937500,0.484375,1.515625,
		-0.937500,0.484375,1.515625,
		0.953125,0.484375,1.546875,
		-0.953125,0.484375,1.546875,
		0.890625,0.671875,1.562500,
		-0.890625,0.671875,1.562500,
		0.703125,0.750000,1.609375,
		-0.703125,0.750000,1.609375,
		0.531250,0.671875,1.640625,
		-0.531250,0.671875,1.640625,
		0.453125,0.484375,1.640625,
		-0.453125,0.484375,1.640625,
		0.531250,0.312500,1.640625,
		-0.531250,0.312500,1.640625,
		0.703125,0.484375,1.656250,
		-0.703125,0.484375,1.656250,
		0.703125,0.234375,1.609375,
		-0.703125,0.234375,1.609375,
		0.890625,0.312500,1.562500,
		-0.890625,0.312500,1.562500,
		0.000000,0.859375,1.484375,
		0.000000,0.703125,1.640625,
		0.000000,-1.359375,1.468750,
		0.000000,-0.640625,1.562500,
		0.000000,-0.375000,1.593750,
		0.000000,-1.546875,1.437500,
		0.000000,0.812500,1.203125,
		0.000000,1.140625,1.140625,
		0.000000,1.796875,-1.093750,
		0.000000,1.125000,-1.703125,
		0.000000,0.140625,-1.656250,
		0.000000,-0.765625,-0.703125,
		0.406250,-0.375000,1.125000,
		-0.406250,-0.375000,1.125000,
		0.625000,-0.875000,1.140625,
		-0.625000,-0.875000,1.140625,
		0.703125,-1.390625,1.140625,
		-0.703125,-1.390625,1.140625,
		0.734375,-1.781250,1.062500,
		-0.734375,-1.781250,1.062500,
		0.656250,-1.890625,1.046875,
		-0.656250,-1.890625,1.046875,
		0.359375,-1.937500,1.109375,
		-0.359375,-1.937500,1.109375,
		0.000000,-1.968750,1.156250,
		0.875000,-0.281250,1.062500,
		-0.875000,-0.281250,1.062500,
		1.265625,-0.078125,1.078125,
		-1.265625,-0.078125,1.078125,
		1.656250,0.296875,0.890625,
		-1.656250,0.296875,0.890625,
		1.718750,0.859375,1.187500,
		-1.718750,0.859375,1.187500,
		1.421875,0.968750,1.250000,
		-1.421875,0.968750,1.250000,
		0.984375,1.203125,1.375000,
		-0.984375,1.203125,1.375000,
		0.640625,1.515625,1.468750,
		-0.640625,1.515625,1.468750,
		0.312500,1.437500,1.515625,
		-0.312500,1.437500,1.515625,
		0.125000,0.984375,1.500000,
		-0.125000,0.984375,1.500000,
		0.328125,0.828125,1.546875,
		-0.328125,0.828125,1.546875,
		0.250000,0.609375,1.531250,
		-0.250000,0.609375,1.531250,
		0.406250,0.187500,1.484375,
		-0.406250,0.187500,1.484375,
		0.750000,0.031250,1.406250,
		-0.750000,0.031250,1.406250,
		0.984375,0.125000,1.343750,
		-0.984375,0.125000,1.343750,
		1.250000,0.375000,1.296875,
		-1.250000,0.375000,1.296875,
		1.281250,0.593750,1.296875,
		-1.281250,0.593750,1.296875,
		1.203125,0.750000,1.328125,
		-1.203125,0.750000,1.328125,
		0.859375,0.875000,1.437500,
		-0.859375,0.875000,1.437500,
		0.500000,0.937500,1.515625,
		-0.500000,0.937500,1.515625,
		0.000000,-1.531250,1.468750,
		0.218750,-1.437500,1.468750,
		-0.218750,-1.437500,1.468750,
		0.234375,-1.671875,1.421875,
		-0.234375,-1.671875,1.421875,
		0.125000,-1.765625,1.390625,
		-0.125000,-1.765625,1.390625,
		0.000000,-1.781250,1.375000,
		0.000000,-0.390625,1.500000,
		0.000000,-0.281250,1.484375,
		0.203125,-0.296875,1.484375,
		-0.203125,-0.296875,1.484375,
		0.250000,-0.453125,1.500000,
		-0.250000,-0.453125,1.500000,
		0.171875,-0.578125,1.484375,
		-0.171875,-0.578125,1.484375,
		0.796875,-0.093750,1.343750,
		-0.796875,-0.093750,1.343750,
		1.234375,0.109375,1.250000,
		-1.234375,0.109375,1.250000,
		1.453125,0.406250,1.203125,
		-1.453125,0.406250,1.203125,
		1.484375,0.750000,1.312500,
		-1.484375,0.750000,1.312500,
		1.375000,0.828125,1.453125,
		-1.375000,0.828125,1.453125,
		0.875000,1.093750,1.593750,
		-0.875000,1.093750,1.593750,
		0.625000,1.281250,1.671875,
		-0.625000,1.281250,1.671875,
		0.406250,1.234375,1.703125,
		-0.406250,1.234375,1.703125,
		0.203125,0.859375,1.687500,
		-0.203125,0.859375,1.687500,
		0.250000,-0.203125,1.625000,
		-0.250000,-0.203125,1.625000,
		0.421875,-0.890625,1.421875,
		-0.421875,-0.890625,1.421875,
		0.500000,-1.406250,1.375000,
		-0.500000,-1.406250,1.375000,
		0.531250,-1.640625,1.328125,
		-0.531250,-1.640625,1.328125,
		0.468750,-1.828125,1.265625,
		-0.468750,-1.828125,1.265625,
		0.328125,-1.859375,1.265625,
		-0.328125,-1.859375,1.265625,
		0.000000,-1.890625,1.281250,
		0.000000,0.093750,1.453125,
		0.000000,0.421875,1.531250,
		0.656250,0.953125,1.484375,
		-0.656250,0.953125,1.484375,
		0.328125,0.281250,1.500000,
		-0.328125,0.281250,1.500000,
		0.265625,0.421875,1.515625,
		-0.265625,0.421875,1.515625,
		0.234375,-1.375000,1.468750,
		-0.234375,-1.375000,1.468750,
		0.156250,-0.890625,1.500000,
		-0.156250,-0.890625,1.500000,
		0.000000,-0.890625,1.500000,
		0.000000,-0.656250,1.484375,
		0.187500,-0.546875,1.562500,
		-0.187500,-0.546875,1.562500,
		0.265625,-0.453125,1.593750,
		-0.265625,-0.453125,1.593750,
		0.218750,-0.265625,1.562500,
		-0.218750,-0.265625,1.562500,
		0.078125,-0.250000,1.562500,
		-0.078125,-0.250000,1.562500,
		0.000000,-0.406250,1.656250,
		0.093750,-0.296875,1.625000,
		-0.093750,-0.296875,1.625000,
		0.187500,-0.312500,1.625000,
		-0.187500,-0.312500,1.625000,
		0.218750,-0.453125,1.656250,
		-0.218750,-0.453125,1.656250,
		0.156250,-0.500000,1.609375,
		-0.156250,-0.500000,1.609375,
		0.000000,-0.578125,1.609375,
		0.515625,-0.625000,1.109375,
		-0.515625,-0.625000,1.109375,
		0.328125,-0.484375,1.421875,
		-0.328125,-0.484375,1.421875,
		0.359375,-0.625000,1.421875,
		-0.359375,-0.625000,1.421875,
		0.468750,-0.500000,1.109375,
		-0.468750,-0.500000,1.109375,
		0.000000,-1.750000,1.375000,
		0.093750,-1.734375,1.375000,
		-0.093750,-1.734375,1.375000,
		0.187500,-1.640625,1.421875,
		-0.187500,-1.640625,1.421875,
		0.187500,-1.484375,1.453125,
		-0.187500,-1.484375,1.453125,
		0.000000,-1.562500,1.312500,
		0.187500,-1.500000,1.328125,
		-0.187500,-1.500000,1.328125,
		0.187500,-1.625000,1.281250,
		-0.187500,-1.625000,1.281250,
		0.093750,-1.703125,1.265625,
		-0.093750,-1.703125,1.265625,
		0.000000,-1.718750,1.265625,
		0.343750,0.437500,1.562500,
		-0.343750,0.437500,1.562500,
		0.375000,0.312500,1.546875,
		-0.375000,0.312500,1.546875,
		0.671875,0.859375,1.515625,
		-0.671875,0.859375,1.515625,
		0.546875,0.843750,1.546875,
		-0.546875,0.843750,1.546875,
		0.843750,0.796875,1.546875,
		-0.843750,0.796875,1.546875,
		1.125000,0.703125,1.390625,
		-1.125000,0.703125,1.390625,
		1.171875,0.578125,1.375000,
		-1.171875,0.578125,1.375000,
		1.156250,0.390625,1.359375,
		-1.156250,0.390625,1.359375,
		0.953125,0.203125,1.437500,
		-0.953125,0.203125,1.437500,
		0.750000,0.125000,1.484375,
		-0.750000,0.125000,1.484375,
		0.453125,0.218750,1.562500,
		-0.453125,0.218750,1.562500,
		0.359375,0.593750,1.562500,
		-0.359375,0.593750,1.562500,
		0.421875,0.750000,1.562500,
		-0.421875,0.750000,1.562500,
		0.468750,0.718750,1.515625,
		-0.468750,0.718750,1.515625,
		0.390625,0.593750,1.515625,
		-0.390625,0.593750,1.515625,
		0.484375,0.250000,1.515625,
		-0.484375,0.250000,1.515625,
		0.750000,0.171875,1.453125,
		-0.750000,0.171875,1.453125,
		0.921875,0.234375,1.406250,
		-0.921875,0.234375,1.406250,
		1.093750,0.421875,1.343750,
		-1.093750,0.421875,1.343750,
		1.109375,0.562500,1.343750,
		-1.109375,0.562500,1.343750,
		1.062500,0.671875,1.359375,
		-1.062500,0.671875,1.359375,
		0.828125,0.781250,1.500000,
		-0.828125,0.781250,1.500000,
		0.562500,0.796875,1.531250,
		-0.562500,0.796875,1.531250,
		0.671875,0.812500,1.500000,
		-0.671875,0.812500,1.500000,
		0.406250,0.343750,1.500000,
		-0.406250,0.343750,1.500000,
		0.390625,0.453125,1.500000,
		-0.390625,0.453125,1.500000,
		0.218750,0.921875,1.218750,
		-0.218750,0.921875,1.218750,
		0.390625,1.328125,1.234375,
		-0.390625,1.328125,1.234375,
		0.671875,1.375000,1.187500,
		-0.671875,1.375000,1.187500,
		0.968750,1.109375,1.109375,
		-0.968750,1.109375,1.109375,
		1.359375,0.906250,0.984375,
		-1.359375,0.906250,0.984375,
		1.593750,0.812500,0.921875,
		-1.593750,0.812500,0.921875,
		1.546875,0.328125,0.750000,
		-1.546875,0.328125,0.750000,
		1.203125,0.000000,0.828125,
		-1.203125,0.000000,0.828125,
		0.875000,-0.187500,0.937500,
		-0.875000,-0.187500,0.937500,
		0.000000,1.796875,0.578125,
		0.000000,1.968750,-0.156250,
		0.000000,-0.390625,-1.343750,
		0.000000,-0.921875,0.375000,
		0.000000,-1.953125,0.921875,
		0.000000,-1.609375,0.687500,
		0.000000,-1.140625,0.640625,
		0.000000,-0.968750,0.562500,
		1.703125,0.468750,0.109375,
		-1.703125,0.468750,0.109375,
		1.718750,0.640625,-0.093750,
		-1.718750,0.640625,-0.093750,
		1.546875,0.531250,-0.875000,
		-1.546875,0.531250,-0.875000,
		0.921875,0.875000,-1.406250,
		-0.921875,0.875000,-1.406250,
		1.468750,-0.093750,0.140625,
		-1.468750,-0.093750,0.140625,
		1.187500,-0.250000,-0.328125,
		-1.187500,-0.250000,-0.328125,
		1.281250,-0.015625,-0.859375,
		-1.281250,-0.015625,-0.859375,
		0.671875,0.109375,-1.328125,
		-0.671875,0.109375,-1.328125,
		0.468750,-0.703125,0.812500,
		-0.468750,-0.703125,0.812500,
		0.359375,-0.828125,0.515625,
		-0.359375,-0.828125,0.515625,
		0.578125,-1.421875,0.765625,
		-0.578125,-1.421875,0.765625,
		0.500000,-1.000000,0.781250,
		-0.500000,-1.000000,0.781250,
		0.656250,-1.828125,0.796875,
		-0.656250,-1.828125,0.796875,
		0.281250,-1.515625,0.734375,
		-0.281250,-1.515625,0.734375,
		0.250000,-1.078125,0.718750,
		-0.250000,-1.078125,0.718750,
		0.328125,-1.890625,0.875000,
		-0.328125,-1.890625,0.875000,
		0.437500,-0.562500,0.859375,
		-0.437500,-0.562500,0.859375,
		0.421875,-0.453125,0.937500,
		-0.421875,-0.453125,0.937500,
		0.406250,-0.343750,1.000000,
		-0.406250,-0.343750,1.000000,
		0.421875,-0.781250,0.328125,
		-0.421875,-0.781250,0.328125,
		0.593750,-0.625000,-0.531250,
		-0.593750,-0.625000,-0.531250,
		0.687500,-0.296875,-1.078125,
		-0.687500,-0.296875,-1.078125,
		0.906250,1.734375,-0.765625,
		-0.906250,1.734375,-0.765625,
		0.906250,1.859375,-0.140625,
		-0.906250,1.859375,-0.140625,
		0.906250,1.703125,0.468750,
		-0.906250,1.703125,0.468750,
		0.921875,1.046875,0.859375,
		-0.921875,1.046875,0.859375,
		1.453125,0.812500,0.671875,
		-1.453125,0.812500,0.671875,
		1.265625,0.906250,0.562500,
		-1.265625,0.906250,0.562500,
		1.281250,1.406250,0.109375,
		-1.281250,1.406250,0.109375,
		1.593750,1.125000,0.250000,
		-1.593750,1.125000,0.250000,
		1.593750,1.234375,-0.234375,
		-1.593750,1.234375,-0.234375,
		1.281250,1.500000,-0.390625,
		-1.281250,1.500000,-0.390625,
		1.281250,1.359375,-0.890625,
		-1.281250,1.359375,-0.890625,
		1.593750,1.078125,-0.718750,
		-1.593750,1.078125,-0.718750,
		1.234375,0.656250,-1.171875,
		-1.234375,0.656250,-1.171875,
		0.968750,0.046875,-1.093750,
		-0.968750,0.046875,-1.093750,
		1.640625,0.656250,-0.406250,
		-1.640625,0.656250,-0.406250,
		0.812500,-0.343750,0.296875,
		-0.812500,-0.343750,0.296875,
		0.859375,-0.390625,-0.421875,
		-0.859375,-0.390625,-0.421875,
		1.781250,0.812500,-0.468750,
		-1.781250,0.812500,-0.468750,
		1.546875,-0.281250,-0.250000,
		-1.546875,-0.281250,-0.250000,
		2.078125,-0.203125,-0.656250,
		-2.078125,-0.203125,-0.656250,
		2.562500,0.109375,-0.859375,
		-2.562500,0.109375,-0.859375,
		2.703125,0.640625,-0.843750,
		-2.703125,0.640625,-0.843750,
		2.468750,1.015625,-0.843750,
		-2.468750,1.015625,-0.843750,
		2.046875,0.953125,-0.625000,
		-2.046875,0.953125,-0.625000,
		2.031250,0.828125,-0.578125,
		-2.031250,0.828125,-0.578125,
		2.375000,0.875000,-0.781250,
		-2.375000,0.875000,-0.781250,
		2.531250,0.578125,-0.812500,
		-2.531250,0.578125,-0.812500,
		2.421875,0.156250,-0.812500,
		-2.421875,0.156250,-0.812500,
		2.062500,-0.078125,-0.609375,
		-2.062500,-0.078125,-0.609375,
		1.656250,-0.140625,-0.265625,
		-1.656250,-0.140625,-0.265625,
		1.843750,0.718750,-0.437500,
		-1.843750,0.718750,-0.437500,
		1.890625,0.609375,-0.578125,
		-1.890625,0.609375,-0.578125,
		1.765625,-0.046875,-0.421875,
		-1.765625,-0.046875,-0.421875,
		2.078125,0.000000,-0.734375,
		-2.078125,0.000000,-0.734375,
		2.375000,0.187500,-0.890625,
		-2.375000,0.187500,-0.890625,
		2.468750,0.500000,-0.890625,
		-2.468750,0.500000,-0.890625,
		2.343750,0.718750,-0.875000,
		-2.343750,0.718750,-0.875000,
		2.046875,0.687500,-0.718750,
		-2.046875,0.687500,-0.718750,
		1.687500,0.578125,-0.421875,
		-1.687500,0.578125,-0.421875,
		1.671875,0.343750,-0.546875,
		-1.671875,0.343750,-0.546875,
		1.515625,0.187500,-0.546875,
		-1.515625,0.187500,-0.546875,
		1.640625,0.171875,-0.546875,
		-1.640625,0.171875,-0.546875,
		1.687500,0.031250,-0.546875,
		-1.687500,0.031250,-0.546875,
		1.625000,-0.031250,-0.546875,
		-1.625000,-0.031250,-0.546875,
		1.453125,0.000000,-0.140625,
		-1.453125,0.000000,-0.140625,
		1.437500,-0.046875,-0.343750,
		-1.437500,-0.046875,-0.343750,
		1.437500,0.078125,-0.375000,
		-1.437500,0.078125,-0.375000,
		1.593750,0.406250,-0.421875,
		-1.593750,0.406250,-0.421875,
		1.781250,0.484375,-0.531250,
		-1.781250,0.484375,-0.531250,
		1.781250,0.468750,-0.640625,
		-1.781250,0.468750,-0.640625,
		1.625000,-0.031250,-0.640625,
		-1.625000,-0.031250,-0.640625,
		1.703125,0.031250,-0.640625,
		-1.703125,0.031250,-0.640625,
		1.656250,0.156250,-0.640625,
		-1.656250,0.156250,-0.640625,
		1.531250,0.187500,-0.640625,
		-1.531250,0.187500,-0.640625,
		1.687500,0.343750,-0.640625,
		-1.687500,0.343750,-0.640625,
		2.078125,0.656250,-0.828125,
		-2.078125,0.656250,-0.828125,
		2.375000,0.687500,-0.968750,
		-2.375000,0.687500,-0.968750,
		2.515625,0.484375,-0.984375,
		-2.515625,0.484375,-0.984375,
		2.421875,0.171875,-0.968750,
		-2.421875,0.171875,-0.968750,
		2.093750,0.000000,-0.843750,
		-2.093750,0.000000,-0.843750,
		1.765625,-0.031250,-0.531250,
		-1.765625,-0.031250,-0.531250,
		1.906250,0.578125,-0.687500,
		-1.906250,0.578125,-0.687500,
		1.781250,0.218750,-0.656250,
		-1.781250,0.218750,-0.656250,
		1.875000,0.125000,-0.671875,
		-1.875000,0.125000,-0.671875,
		2.000000,0.250000,-0.734375,
		-2.000000,0.250000,-0.734375,
		1.921875,0.343750,-0.703125,
		-1.921875,0.343750,-0.703125,
		2.031250,0.468750,-0.750000,
		-2.031250,0.468750,-0.750000,
		2.109375,0.375000,-0.765625,
		-2.109375,0.375000,-0.765625,
		2.218750,0.421875,-0.781250,
		-2.218750,0.421875,-0.781250,
		2.171875,0.546875,-0.781250,
		-2.171875,0.546875,-0.781250,
		2.046875,0.875000,-0.968750,
		-2.046875,0.875000,-0.968750,
		2.500000,0.937500,-1.093750,
		-2.500000,0.937500,-1.093750,
		2.734375,0.593750,-1.000000,
		-2.734375,0.593750,-1.000000,
		2.625000,0.109375,-1.062500,
		-2.625000,0.109375,-1.062500,
		2.078125,-0.171875,-0.984375,
		-2.078125,-0.171875,-0.984375,
		1.578125,-0.250000,-0.656250,
		-1.578125,-0.250000,-0.656250,
		1.718750,0.765625,-0.765625,
		-1.718750,0.765625,-0.765625
};

static GLint g_index_buffer_data[] = {
		47,3,45,
		4,48,46,
		45,5,43,
		6,46,44,
		3,7,5,
		8,4,6,
		1,9,3,
		10,2,4,
		11,15,9,
		16,12,10,
		9,17,7,
		18,10,8,
		21,17,15,
		22,18,20,
		13,21,15,
		22,14,16,
		23,27,21,
		28,24,22,
		27,19,21,
		28,20,30,
		33,29,27,
		34,30,32,
		35,27,25,
		36,28,34,
		37,33,35,
		38,34,40,
		39,31,33,
		40,32,42,
		45,41,39,
		46,42,44,
		47,39,37,
		48,40,46,
		37,49,47,
		38,50,52,
		35,51,37,
		36,52,54,
		25,53,35,
		26,54,56,
		23,55,25,
		24,56,58,
		23,59,57,
		60,24,58,
		13,63,59,
		64,14,60,
		11,65,63,
		66,12,64,
		1,49,65,
		50,2,66,
		61,65,49,
		50,66,62,
		63,65,61,
		62,66,64,
		61,59,63,
		64,60,62,
		61,57,59,
		60,58,62,
		61,55,57,
		58,56,62,
		61,53,55,
		56,54,62,
		61,51,53,
		54,52,62,
		61,49,51,
		52,50,62,
		174,91,89,
		175,91,176,
		172,89,87,
		173,90,175,
		85,172,87,
		173,86,88,
		83,170,85,
		171,84,86,
		81,168,83,
		169,82,84,
		79,146,164,
		147,80,165,
		94,146,92,
		95,147,149,
		94,150,148,
		151,95,149,
		98,150,96,
		99,151,153,
		100,152,98,
		101,153,155,
		102,154,100,
		103,155,157,
		102,158,156,
		159,103,157,
		106,158,104,
		107,159,161,
		108,160,106,
		109,161,163,
		67,162,108,
		67,163,68,
		128,162,110,
		129,163,161,
		128,158,160,
		159,129,161,
		156,179,126,
		157,180,159,
		154,126,124,
		155,127,157,
		152,124,122,
		153,125,155,
		150,122,120,
		151,123,153,
		148,120,118,
		149,121,151,
		146,118,116,
		147,119,149,
		164,116,114,
		165,117,147,
		114,177,164,
		177,115,165,
		162,112,110,
		163,113,68,
		112,178,183,
		178,113,184,
		181,178,177,
		182,178,184,
		135,176,174,
		176,136,175,
		133,174,172,
		175,134,173,
		133,170,131,
		134,171,173,
		166,185,168,
		186,167,169,
		131,168,185,
		169,132,186,
		190,187,144,
		190,188,189,
		187,69,185,
		188,69,189,
		131,69,130,
		132,69,186,
		142,191,144,
		192,143,145,
		140,193,142,
		194,141,143,
		197,140,139,
		198,141,196,
		71,139,138,
		71,139,198,
		144,70,190,
		145,70,192,
		191,208,70,
		192,208,207,
		71,200,197,
		201,71,198,
		197,202,195,
		203,198,196,
		202,193,195,
		203,194,205,
		193,206,191,
		207,194,192,
		204,200,199,
		205,201,203,
		199,206,204,
		207,199,205,
		139,164,177,
		165,139,177,
		140,211,164,
		212,141,165,
		144,211,142,
		145,212,214,
		187,213,144,
		188,214,167,
		209,166,81,
		210,167,214,
		215,213,209,
		216,214,212,
		79,211,215,
		212,80,216,
		130,222,131,
		130,223,72,
		133,222,220,
		223,134,221,
		135,220,218,
		221,136,219,
		137,218,217,
		219,137,217,
		218,231,217,
		219,231,230,
		218,227,229,
		228,219,230,
		220,225,227,
		226,221,228,
		72,225,222,
		72,226,224,
		224,229,225,
		230,224,226,
		225,229,227,
		228,230,226,
		183,234,232,
		235,184,233,
		112,232,254,
		233,113,255,
		112,256,110,
		113,257,255,
		114,234,181,
		115,235,253,
		114,250,252,
		251,115,253,
		116,248,250,
		249,117,251,
		118,246,248,
		247,119,249,
		120,244,246,
		245,121,247,
		124,244,122,
		125,245,243,
		126,242,124,
		127,243,241,
		126,236,240,
		237,127,241,
		179,238,236,
		239,180,237,
		128,256,238,
		257,129,239,
		256,276,238,
		257,277,259,
		236,276,278,
		277,237,279,
		236,274,240,
		237,275,279,
		240,272,242,
		241,273,275,
		244,272,270,
		273,245,271,
		244,268,246,
		245,269,271,
		248,268,266,
		269,249,267,
		248,264,250,
		249,265,267,
		250,262,252,
		251,263,265,
		234,262,280,
		263,235,281,
		256,260,258,
		261,257,259,
		254,282,260,
		283,255,261,
		232,280,282,
		281,233,283,
		67,284,73,
		285,67,73,
		108,286,284,
		287,109,285,
		104,286,106,
		105,287,289,
		102,288,104,
		103,289,291,
		100,290,102,
		101,291,293,
		100,294,292,
		295,101,293,
		96,294,98,
		97,295,297,
		96,298,296,
		299,97,297,
		94,300,298,
		301,95,299,
		309,338,308,
		309,339,329,
		308,336,307,
		308,337,339,
		307,340,306,
		307,341,337,
		89,306,340,
		306,90,341,
		87,340,334,
		341,88,335,
		85,334,330,
		335,86,331,
		83,330,332,
		331,84,333,
		330,338,332,
		339,331,333,
		334,336,330,
		335,337,341,
		332,328,326,
		333,329,339,
		81,332,326,
		333,82,327,
		342,215,209,
		343,216,345,
		326,209,81,
		327,210,343,
		215,346,79,
		216,347,345,
		346,92,79,
		347,93,301,
		324,304,77,
		325,304,353,
		352,78,304,
		353,78,351,
		78,348,305,
		349,78,305,
		305,328,309,
		329,305,309,
		328,342,326,
		329,343,349,
		296,318,310,
		319,297,311,
		316,77,76,
		317,77,325,
		358,303,302,
		359,303,357,
		303,354,75,
		355,303,75,
		75,316,76,
		317,75,76,
		292,362,364,
		363,293,365,
		364,368,366,
		369,365,367,
		366,370,372,
		371,367,373,
		372,376,374,
		377,373,375,
		378,376,314,
		379,377,375,
		316,374,378,
		375,317,379,
		354,372,374,
		373,355,375,
		356,366,372,
		367,357,373,
		358,364,366,
		365,359,367,
		292,360,290,
		293,361,365,
		360,302,74,
		361,302,359,
		284,288,290,
		289,285,291,
		284,360,74,
		361,285,74,
		73,284,74,
		74,285,73,
		296,362,294,
		297,363,311,
		310,368,362,
		369,311,363,
		312,370,368,
		371,313,369,
		376,382,314,
		377,383,371,
		350,384,348,
		351,385,387,
		384,320,318,
		385,321,387,
		298,384,318,
		385,299,319,
		300,342,384,
		343,301,385,
		342,348,384,
		385,349,343,
		300,346,344,
		345,347,301,
		322,378,314,
		323,379,381,
		378,324,316,
		379,325,381,
		386,322,320,
		387,323,381,
		352,386,350,
		353,387,381,
		324,380,352,
		353,381,325,
		388,402,400,
		389,403,415,
		400,404,398,
		405,401,399,
		404,396,398,
		405,397,407,
		406,394,396,
		407,395,409,
		408,392,394,
		409,393,411,
		392,412,390,
		413,393,391,
		410,418,412,
		419,411,413,
		408,420,410,
		421,409,411,
		424,408,406,
		425,409,423,
		426,406,404,
		427,407,425,
		428,404,402,
		429,405,427,
		402,416,428,
		417,403,429,
		320,442,318,
		321,443,445,
		390,444,320,
		391,445,413,
		310,442,312,
		443,311,313,
		382,414,388,
		415,383,389,
		412,440,444,
		441,413,445,
		446,440,438,
		447,441,445,
		434,438,436,
		439,435,437,
		448,434,432,
		449,435,447,
		448,450,430,
		449,451,433,
		430,416,414,
		431,417,451,
		312,430,382,
		431,313,383,
		442,448,312,
		443,449,447,
		442,444,446,
		447,445,443,
		416,452,476,
		453,417,477,
		432,452,450,
		433,453,463,
		432,460,462,
		461,433,463,
		436,460,434,
		437,461,459,
		438,458,436,
		439,459,457,
		438,454,456,
		455,439,457,
		440,474,454,
		475,441,455,
		428,476,464,
		477,429,465,
		426,464,466,
		465,427,467,
		424,466,468,
		467,425,469,
		424,470,422,
		425,471,469,
		422,472,420,
		423,473,471,
		420,474,418,
		421,475,473,
		456,478,458,
		457,479,481,
		480,484,478,
		481,485,483,
		484,488,486,
		489,485,487,
		488,492,486,
		489,493,491,
		464,486,492,
		487,465,493,
		484,476,452,
		485,477,487,
		462,484,452,
		463,485,479,
		458,462,460,
		463,459,461,
		474,456,454,
		475,457,481,
		472,480,474,
		481,473,475,
		488,472,470,
		489,473,483,
		490,470,468,
		491,471,489,
		466,490,468,
		491,467,469,
		464,492,466,
		467,493,465,
		392,504,502,
		505,393,503,
		394,502,500,
		503,395,501,
		394,498,396,
		395,499,501,
		396,496,398,
		397,497,499,
		398,494,400,
		399,495,497,
		400,506,388,
		401,507,495,
		502,506,494,
		503,507,505,
		494,500,502,
		501,495,503,
		496,498,500,
		501,499,497,
		382,506,314,
		383,507,389,
		314,504,322,
		505,315,323,
		320,504,390,
		505,321,391,
		47,1,3,
		4,2,48,
		45,3,5,
		6,4,46,
		3,9,7,
		8,10,4,
		1,11,9,
		10,12,2,
		11,13,15,
		16,14,12,
		9,15,17,
		18,16,10,
		21,19,17,
		22,16,18,
		13,23,21,
		22,24,14,
		23,25,27,
		28,26,24,
		27,29,19,
		28,22,20,
		33,31,29,
		34,28,30,
		35,33,27,
		36,26,28,
		37,39,33,
		38,36,34,
		39,41,31,
		40,34,32,
		45,43,41,
		46,40,42,
		47,45,39,
		48,38,40,
		37,51,49,
		38,48,50,
		35,53,51,
		36,38,52,
		25,55,53,
		26,36,54,
		23,57,55,
		24,26,56,
		23,13,59,
		60,14,24,
		13,11,63,
		64,12,14,
		11,1,65,
		66,2,12,
		1,47,49,
		50,48,2,
		174,176,91,
		175,90,91,
		172,174,89,
		173,88,90,
		85,170,172,
		173,171,86,
		83,168,170,
		171,169,84,
		81,166,168,
		169,167,82,
		79,92,146,
		147,93,80,
		94,148,146,
		95,93,147,
		94,96,150,
		151,97,95,
		98,152,150,
		99,97,151,
		100,154,152,
		101,99,153,
		102,156,154,
		103,101,155,
		102,104,158,
		159,105,103,
		106,160,158,
		107,105,159,
		108,162,160,
		109,107,161,
		67,68,162,
		67,109,163,
		128,160,162,
		129,111,163,
		128,179,158,
		159,180,129,
		156,158,179,
		157,127,180,
		154,156,126,
		155,125,127,
		152,154,124,
		153,123,125,
		150,152,122,
		151,121,123,
		148,150,120,
		149,119,121,
		146,148,118,
		147,117,119,
		164,146,116,
		165,115,117,
		114,181,177,
		177,182,115,
		162,68,112,
		163,111,113,
		112,68,178,
		178,68,113,
		181,183,178,
		182,177,178,
		135,137,176,
		176,137,136,
		133,135,174,
		175,136,134,
		133,172,170,
		134,132,171,
		166,187,185,
		186,188,167,
		131,170,168,
		169,171,132,
		190,189,187,
		190,145,188,
		187,189,69,
		188,186,69,
		131,185,69,
		132,130,69,
		142,193,191,
		192,194,143,
		140,195,193,
		194,196,141,
		197,195,140,
		198,139,141,
		71,197,139,
		71,138,139,
		144,191,70,
		145,190,70,
		191,206,208,
		192,70,208,
		71,199,200,
		201,199,71,
		197,200,202,
		203,201,198,
		202,204,193,
		203,196,194,
		193,204,206,
		207,205,194,
		204,202,200,
		205,199,201,
		199,208,206,
		207,208,199,
		139,140,164,
		165,141,139,
		140,142,211,
		212,143,141,
		144,213,211,
		145,143,212,
		187,166,213,
		188,145,214,
		209,213,166,
		210,82,167,
		215,211,213,
		216,210,214,
		79,164,211,
		212,165,80,
		130,72,222,
		130,132,223,
		133,131,222,
		223,132,134,
		135,133,220,
		221,134,136,
		137,135,218,
		219,136,137,
		218,229,231,
		219,217,231,
		218,220,227,
		228,221,219,
		220,222,225,
		226,223,221,
		72,224,225,
		72,223,226,
		224,231,229,
		230,231,224,
		183,181,234,
		235,182,184,
		112,183,232,
		233,184,113,
		112,254,256,
		113,111,257,
		114,252,234,
		115,182,235,
		114,116,250,
		251,117,115,
		116,118,248,
		249,119,117,
		118,120,246,
		247,121,119,
		120,122,244,
		245,123,121,
		124,242,244,
		125,123,245,
		126,240,242,
		127,125,243,
		126,179,236,
		237,180,127,
		179,128,238,
		239,129,180,
		128,110,256,
		257,111,129,
		256,258,276,
		257,239,277,
		236,238,276,
		277,239,237,
		236,278,274,
		237,241,275,
		240,274,272,
		241,243,273,
		244,242,272,
		273,243,245,
		244,270,268,
		245,247,269,
		248,246,268,
		269,247,249,
		248,266,264,
		249,251,265,
		250,264,262,
		251,253,263,
		234,252,262,
		263,253,235,
		256,254,260,
		261,255,257,
		254,232,282,
		283,233,255,
		232,234,280,
		281,235,233,
		67,108,284,
		285,109,67,
		108,106,286,
		287,107,109,
		104,288,286,
		105,107,287,
		102,290,288,
		103,105,289,
		100,292,290,
		101,103,291,
		100,98,294,
		295,99,101,
		96,296,294,
		97,99,295,
		96,94,298,
		299,95,97,
		94,92,300,
		301,93,95,
		309,328,338,
		309,308,339,
		308,338,336,
		308,307,337,
		307,336,340,
		307,306,341,
		89,91,306,
		306,91,90,
		87,89,340,
		341,90,88,
		85,87,334,
		335,88,86,
		83,85,330,
		331,86,84,
		330,336,338,
		339,337,331,
		334,340,336,
		335,331,337,
		332,338,328,
		333,327,329,
		81,83,332,
		333,84,82,
		342,344,215,
		343,210,216,
		326,342,209,
		327,82,210,
		215,344,346,
		216,80,347,
		346,300,92,
		347,80,93,
		324,352,304,
		325,77,304,
		352,350,78,
		353,304,78,
		78,350,348,
		349,351,78,
		305,348,328,
		329,349,305,
		328,348,342,
		329,327,343,
		296,298,318,
		319,299,297,
		316,324,77,
		317,76,77,
		358,356,303,
		359,302,303,
		303,356,354,
		355,357,303,
		75,354,316,
		317,355,75,
		292,294,362,
		363,295,293,
		364,362,368,
		369,363,365,
		366,368,370,
		371,369,367,
		372,370,376,
		377,371,373,
		378,374,376,
		379,315,377,
		316,354,374,
		375,355,317,
		354,356,372,
		373,357,355,
		356,358,366,
		367,359,357,
		358,360,364,
		365,361,359,
		292,364,360,
		293,291,361,
		360,358,302,
		361,74,302,
		284,286,288,
		289,287,285,
		284,290,360,
		361,291,285,
		296,310,362,
		297,295,363,
		310,312,368,
		369,313,311,
		312,382,370,
		371,383,313,
		376,370,382,
		377,315,383,
		350,386,384,
		351,349,385,
		384,386,320,
		385,319,321,
		298,300,384,
		385,301,299,
		300,344,342,
		343,345,301,
		322,380,378,
		323,315,379,
		378,380,324,
		379,317,325,
		386,380,322,
		387,321,323,
		352,380,386,
		353,351,387,
		388,414,402,
		389,401,403,
		400,402,404,
		405,403,401,
		404,406,396,
		405,399,397,
		406,408,394,
		407,397,395,
		408,410,392,
		409,395,393,
		392,410,412,
		413,411,393,
		410,420,418,
		419,421,411,
		408,422,420,
		421,423,409,
		424,422,408,
		425,407,409,
		426,424,406,
		427,405,407,
		428,426,404,
		429,403,405,
		402,414,416,
		417,415,403,
		320,444,442,
		321,319,443,
		390,412,444,
		391,321,445,
		310,318,442,
		443,319,311,
		382,430,414,
		415,431,383,
		412,418,440,
		441,419,413,
		446,444,440,
		447,439,441,
		434,446,438,
		439,447,435,
		448,446,434,
		449,433,435,
		448,432,450,
		449,431,451,
		430,450,416,
		431,415,417,
		312,448,430,
		431,449,313,
		442,446,448,
		443,313,449,
		416,450,452,
		453,451,417,
		432,462,452,
		433,451,453,
		432,434,460,
		461,435,433,
		436,458,460,
		437,435,461,
		438,456,458,
		439,437,459,
		438,440,454,
		455,441,439,
		440,418,474,
		475,419,441,
		428,416,476,
		477,417,429,
		426,428,464,
		465,429,427,
		424,426,466,
		467,427,425,
		424,468,470,
		425,423,471,
		422,470,472,
		423,421,473,
		420,472,474,
		421,419,475,
		456,480,478,
		457,459,479,
		480,482,484,
		481,479,485,
		484,482,488,
		489,483,485,
		488,490,492,
		489,487,493,
		464,476,486,
		487,477,465,
		484,486,476,
		485,453,477,
		462,478,484,
		463,453,485,
		458,478,462,
		463,479,459,
		474,480,456,
		475,455,457,
		472,482,480,
		481,483,473,
		488,482,472,
		489,471,473,
		490,488,470,
		491,469,471,
		466,492,490,
		491,493,467,
		392,390,504,
		505,391,393,
		394,392,502,
		503,393,395,
		394,500,498,
		395,397,499,
		396,498,496,
		397,399,497,
		398,496,494,
		399,401,495,
		400,494,506,
		401,389,507,
		502,504,506,
		503,495,507,
		494,496,500,
		501,497,495,
		382,388,506,
		383,315,507,
		314,506,504,
		505,507,315,
		320,322,504,
		505,323,321
};


void draw_suzanne()
{
	for(int i = 0; i < NUM_INDICES; i += 3)
	{
		int index = g_index_buffer_data[i] - 1;
		glBegin(GL_TRIANGLES);
		glVertex3f(g_vertex_buffer_data[index * 3], g_vertex_buffer_data[(index * 3) + 1], g_vertex_buffer_data[(index * 3) + 2]);
		index = g_index_buffer_data[i+1] - 1;
		glVertex3f(g_vertex_buffer_data[index * 3], g_vertex_buffer_data[(index * 3) + 1], g_vertex_buffer_data[(index * 3) + 2]);
		index = g_index_buffer_data[i+2] - 1;
		glVertex3f(g_vertex_buffer_data[index * 3], g_vertex_buffer_data[(index * 3) + 1], g_vertex_buffer_data[(index * 3) + 2]);
		glEnd();
	}
}

int main(int, char**)
{
	ThreadCtl(_NTO_TCTL_IO, NULL); // Should the driver do this?!
	rush3d_card_init();

    bool running = true;

    printf("GL_VENDOR: %s\n", glGetString(GL_VENDOR));
    printf("GL_RENDERER: %s\n", glGetString(GL_RENDERER));
    printf("GL_VERSION: %s\n", glGetString(GL_VERSION));

    GLfloat aspect = (GLfloat)VIDEO_WIDTH / (GLfloat)VIDEO_HEIGHT; // Compute aspect ratio of window
    glMatrixMode(GL_PROJECTION);                                   // To operate on the Projection matrix
    glLoadIdentity();                                              // Reset
                                                                   // Let's work out the view frustum (this is ripped from Quake, cheers John)
    GLdouble xmin, xmax, ymin, ymax;
    ymax = 4.0f * tan(60.0f * M_PI / 360.0);
    ymin = -ymax;
    xmin = ymin * aspect;
    xmax = ymax * aspect;
    glFrustum(xmin, xmax, ymin, ymax, 4, 10);
    GLfloat angle = 0.0f;
    GLfloat z = -8.0f;

    while(running)
    {
        angle -= 1.0f;

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glTranslatef(0.0f, 0.0f, 0.0f);
        glRotatef(angle, 1.0f, 0.0f, 1.0f);
        glTranslatef(0.0f, 0.0f, z);
        draw_suzanne();

        rush3d_swap_buffers();
    }

    return 0;
}
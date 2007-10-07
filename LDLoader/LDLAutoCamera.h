#ifndef __LDLAUTOCAMERA_H__
#define __LDLAUTOCAMERA_H__

// This is conversion of Lars Hassing's auto camera code from L3P.  It computes
// the correct distance and pan amount for the camera so that the viewing
// pyramid will be positioned in the closest possible position, such that the
// model just touches the edges of the view on the top and bottom, the left and
// right, or all four.
// After processing all the model data for the current camera angle, it ends up
// with 6 equations with 6 unknowns.  It uses a matrix solving routine to solve
// these.  The 6 values seem to be the X, Y, and Z coordinates of two points.
// Once it has the values, it decides which point is the correct point, and then
// uses that as the camera location.

#include <TCFoundation/TCObject.h>
#include <TCFoundation/TCVector.h>
#include <LDLoader/LDLCamera.h>

class LDLModel;

#define L3ORDERM 6
#define L3ORDERN 6

class LDLAutoCamera : public TCObject
{
public:
	LDLAutoCamera(void);
	void setModel(const LDLModel *value);
	void setModelCenter(const TCVector &value);
	void setRotationMatrix(const TCFloat *value);
	void setCamera(const LDLCamera &value);
	void setCameraGlobe(const char *value);
	void setDistanceMultiplier(TCFloat value);
	void setWidth(TCFloat value);
	void setHeight(TCFloat value);
	void setMargin(TCFloat value);
	void setFov(TCFloat value);

	void zoomToFit(void);
	const LDLCamera &getCamera(void) const { return m_camera; }
protected:
	~LDLAutoCamera(void);
	void dealloc(void);

	void preCalcCamera(void);
	void scanCameraPoint(const TCVector &point);
	int L3Solve6(TCFloat x[L3ORDERN], const TCFloat A[L3ORDERM][L3ORDERN],
		const TCFloat b[L3ORDERM]);

	const LDLModel *m_model;
	LDLCamera m_camera;
	TCVector m_modelCenter;
	TCFloat m_rotationMatrix[16];
	TCFloat m_globeRadius;
	bool m_haveGlobeRadius;
	TCFloat m_distanceMultiplier;
	TCFloat m_width;
	TCFloat m_height;
	TCFloat m_margin;
	TCFloat m_fov;
#ifdef _DEBUG
	int m_numPoints;
#endif // _DEBUG
	struct CameraData
	{
		CameraData(void)
			:direction(0.0f, 0.0f, -1.0f),
			horizontal(1.0f, 0.0f, 0.0f),
			vertical(0.0f, -1.0f, 0.0f),
			horMin(1e6),
			horMax(-1e6),
			verMin(1e6),
			verMax(-1e6)
		{
			int i;

			for (i = 0; i < 4; i++)
			{
				dMin[i] = 1e6;
			}
		}
		TCVector direction;
		TCVector horizontal;
		TCVector vertical;
		TCVector normal[4];
		TCFloat dMin[4];
		TCFloat horMin;
		TCFloat horMax;
		TCFloat verMin;
		TCFloat verMax;
		TCFloat fov;
	} *m_cameraData;
};

#endif // __LDLAUTOCAMERA_H__
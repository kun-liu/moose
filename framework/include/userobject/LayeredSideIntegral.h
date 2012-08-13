/****************************************************************/
/*               DO NOT MODIFY THIS HEADER                      */
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*           (c) 2010 Battelle Energy Alliance, LLC             */
/*                   ALL RIGHTS RESERVED                        */
/*                                                              */
/*          Prepared by Battelle Energy Alliance, LLC           */
/*            Under Contract No. DE-AC07-05ID14517              */
/*            With the U. S. Department of Energy               */
/*                                                              */
/*            See COPYRIGHT for full restrictions               */
/****************************************************************/

#ifndef LAYEREDSIDEINTEGRAL_H
#define LAYEREDSIDEINTEGRAL_H

#include "SideIntegral.h"

// libmesh includes
#include "mesh_tools.h"

//Forward Declarations
class LayeredSideIntegral;

template<>
InputParameters validParams<LayeredSideIntegral>();

/**
 * This UserObject computes volume integrals of a variable storing partial sums for the specified number of intervals in a direction (x,y,z).c
 */
class LayeredSideIntegral : public SideIntegral
{
public:
  LayeredSideIntegral(const std::string & name, InputParameters parameters);

  /**
   * Given a Point return the integral value associated with the layer that point falls in.
   *
   * @param p The point to look for in the layers.
   */
  Real integralValue(Point p) const;

  virtual void initialize();
  virtual void execute();
  virtual void finalize();
  virtual void threadJoin(const UserObject & y);

protected:
  /**
   * Helper function to return the layer the point lies in.
   * @param p The point.
   * @return The layer the Point is found in.
   */
  unsigned int getLayer(Point p) const;

  /// The MooseEnum direction the layers are going in
  MooseEnum _direction_enum;

  /// The component direction the layers are going in.  We cache this for speed (so we're not always going through the MooseEnum)
  unsigned int _direction;

  /// Number of layers to split the mesh into
  unsigned int _num_layers;

  /// Value of the integral for each layer
  std::vector<Real> _layer_values;

  Real _direction_min;
  Real _direction_max;
};

#endif
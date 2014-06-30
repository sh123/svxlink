/**
@file	 SigLevDetNoise.h
@brief   A simple signal level detector based on noise measurements
@author  Tobias Blomberg / SM0SVX
@date	 2006-05-07

\verbatim
SvxLink - A Multi Purpose Voice Services System for Ham Radio Use
Copyright (C) 2003-2008 Tobias Blomberg / SM0SVX

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
\endverbatim
*/

#ifndef SIG_LEV_DET_NOISE_INCLUDED
#define SIG_LEV_DET_NOISE_INCLUDED


/****************************************************************************
 *
 * System Includes
 *
 ****************************************************************************/

#include <list>
#include <set>
#include <sigc++/sigc++.h>


/****************************************************************************
 *
 * Project Includes
 *
 ****************************************************************************/

#include <AsyncAudioSink.h>


/****************************************************************************
 *
 * Local Includes
 *
 ****************************************************************************/

#include "SigLevDet.h"


/****************************************************************************
 *
 * Forward declarations
 *
 ****************************************************************************/

namespace Async
{
  class AudioFilter;
  class SigCAudioSink;
};


/****************************************************************************
 *
 * Namespace
 *
 ****************************************************************************/

//namespace MyNameSpace
//{


/****************************************************************************
 *
 * Forward declarations of classes inside of the declared namespace
 *
 ****************************************************************************/

  

/****************************************************************************
 *
 * Defines & typedefs
 *
 ****************************************************************************/



/****************************************************************************
 *
 * Exported Global Variables
 *
 ****************************************************************************/



/****************************************************************************
 *
 * Class definitions
 *
 ****************************************************************************/

/**
@brief	A simple noise measuring signal level detector
@author Tobias Blomberg / SM0SVX
@date   2006-05-07
*/
class SigLevDetNoise : public SigLevDet
{
  public:
    /**
     * @brief 	Default constuctor
     */
    explicit SigLevDetNoise(int sample_rate);
  
    /**
     * @brief 	Destructor
     */
    ~SigLevDetNoise(void);
    
    /**
     * @brief 	Set the detector slope
     * @param 	slope The detector slope to set
     */
    void setDetectorSlope(float slope);

    /**
     * @brief 	Set the detector offset
     * @param 	offset The offset to set
     */
    void setDetectorOffset(float offset);
  
    /**
     * @brief	Set the interval for continuous updates
     * @param	interval_ms The update interval, in milliseconds, to use.
     * 
     * This function will set up how often the signal level detector will
     * report the signal strength.
     */
    virtual void setContinuousUpdateInterval(int interval_ms);
    
    /**
     * @brief	Set the integration time to use
     * @param	time_ms The integration time in milliseconds
     * 
     * This function will set up the integration time for the signal level
     * detector. That is, the detector will build a mean value of the
     * detected signal strengths over the given integration time.
     */
    virtual void setIntegrationTime(int time_ms);
    
    /**
     * @brief 	Read the latest calculated signal level
     * @return	Returns the latest calculated signal level
     */
    virtual float lastSiglev(void) const;
     
    /**
     * @brief   Read the integrated siglev value
     * @return  Returns the integrated siglev value
     */
    virtual float siglevIntegrated(void) const;
    
    /**
     * @brief   Reset the signal level detector
     */
    virtual void reset(void);
     
    
  protected:
    
  private:
    typedef std::multiset<double> SsSet;
    typedef SsSet::const_iterator SsSetIter;
    typedef std::list<SsSetIter>  SsIndexList;

    static const unsigned BLOCK_TIME          = 25;     // milliseconds
    static const float    BOGUS_ABOVE_SIGLEV  = 120.0f;

    const unsigned            sample_rate;
    const unsigned            block_len;
    Async::AudioFilter	      *filter;
    Async::SigCAudioSink      *sigc_sink;
    float     	      	      slope;
    float     	      	      offset;
    int			      update_interval;
    int			      update_counter;
    unsigned		      integration_time;
    SsSet                     ss_values;
    SsIndexList               ss_idx;
    double                    ss;
    unsigned                  ss_cnt;
    
    SigLevDetNoise(const SigLevDetNoise&);
    SigLevDetNoise& operator=(const SigLevDetNoise&);
    int processSamples(float *samples, int count);
    
};  /* class SigLevDetNoise */


//} /* namespace */

#endif /* SIG_LEV_DET_NOISE_INCLUDED */



/*
 * This file has not been truncated
 */

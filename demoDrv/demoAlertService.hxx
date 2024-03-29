#ifndef demoALERTSERVICE_H_
#define demoALERTSERVICE_H_

#ifndef _ALERTSERVICE_H_
#include <AlertService.hxx>
#endif

#include <DrvManager.hxx>


class demoAlertService : public AlertService
{
  public:

    /// Constructor
    demoAlertService();

    /// Destruktur
    virtual  ~demoAlertService();
    
    /** callback function. This function is called, when the driver should acknowledge the alert
        related to the address given in the HWObject.
        @param objPtr address for which the alert should be acknowledged
        @return PVSS_TRUE on success, PVSS_FALSE if the acknowledge fails
        @classification public use, overload
    */
    PVSSboolean ackAlertInHW(AlertObject *alertPtr, HWObject *objPtr) override;

    /** callback function. this function is used to notify the driver about successful acknowledgement 
        of the alert in PVSS.
        @param alertPtr pointer to alert data 
        @param objPtr pointer to reference HW object 
        @classification public use, overload
    */
    void ackConfirmCB(const AlertObject *alertPtr, const HWObject *adrPtr) override;

    /** callback function. this function is used to notify the driver about alert changes in the _add_values.
        The first call signals that EV has confirmed the new alert instance.
        @param alertPtr pointer to alert data 
        @param objPtr pointer to reference HW object 
        @classification public use, overload
    */
    void changeNotificationCB(const AlertObject *alertPtr, const HWObject *adrPtr) override;

    /** callback function. this function is used to notify the driver about the removal of the given alert.
        this is the final callback before the alert is discarded from the active alert list.
        This callback is also triggered when a PVSS datapoint element holding alerts is deleted.
        @param alertPtr pointer to alert data 
        @param objPtr pointer to reference HW object 
        @classification public use, overload
    */
    void invisibleConfirmCB(const AlertObject *alertPtr, const HWObject *adrPtr) override;
};

#endif

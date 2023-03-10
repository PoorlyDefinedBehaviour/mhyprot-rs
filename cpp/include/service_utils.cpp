#include "service_utils.hpp"

//
// open service control manager to operate services
//
SC_HANDLE service_utils::open_sc_manager()
{
    return OpenSCManager(nullptr, nullptr, SC_MANAGER_CREATE_SERVICE);
}

//
// create a new service
// sc create myservice binPath="" type=kernel
//
SC_HANDLE service_utils::create_service(const std::string_view driver_path)
{
    SC_HANDLE sc_manager_handle = open_sc_manager();

    CHECK_SC_MANAGER_HANDLE(sc_manager_handle, (SC_HANDLE)INVALID_HANDLE_VALUE);

    SC_HANDLE cvrl_service_handle = CreateService(
        sc_manager_handle,
        (LPCWSTR)CVRL_SERVICE_NAME,
        (LPCWSTR)CVRL_DISPLAY_NAME,
        SERVICE_START | SERVICE_STOP | DELETE,
        SERVICE_KERNEL_DRIVER, SERVICE_DEMAND_START, SERVICE_ERROR_IGNORE,
        (LPCWSTR)(driver_path.data()), nullptr, nullptr, nullptr, nullptr, nullptr);

    if (!CHECK_HANDLE(cvrl_service_handle))
    {
        const auto last_error = GetLastError();

        if (last_error == ERROR_SERVICE_EXISTS)
        {
            logger::log("[+] the service already exists, open handle\n");

            return OpenService(
                sc_manager_handle,
                (LPCWSTR)CVRL_SERVICE_NAME,
                SERVICE_START | SERVICE_STOP | DELETE);
        }

        logger::log("[!] failed to create %s service. (0x%lX)\n", CVRL_SERVICE_NAME, GetLastError());
        CloseServiceHandle(sc_manager_handle);
        return (SC_HANDLE)(INVALID_HANDLE_VALUE);
    }

    CloseServiceHandle(sc_manager_handle);

    return cvrl_service_handle;
}

//
// delete the service
// sc delete myservice
//
bool service_utils::delete_service(SC_HANDLE service_handle, bool close_on_fail, bool close_on_success)
{
    SC_HANDLE sc_manager_handle = open_sc_manager();

    CHECK_SC_MANAGER_HANDLE(sc_manager_handle, false);

    if (!DeleteService(service_handle))
    {
        const auto last_error = GetLastError();

        if (last_error == ERROR_SERVICE_MARKED_FOR_DELETE)
        {
            CloseServiceHandle(sc_manager_handle);
            return true;
        }

        logger::log("[!] failed to delete the service. (0x%lX)\n", GetLastError());
        CloseServiceHandle(sc_manager_handle);
        if (close_on_fail)
            CloseServiceHandle(service_handle);
        return false;
    }

    CloseServiceHandle(sc_manager_handle);
    if (close_on_success)
        CloseServiceHandle(service_handle);

    return true;
}

//
// start the service
// sc start myservice
//
bool service_utils::start_service(SC_HANDLE service_handle)
{
    const DWORD SERVICE_ALREADY_RUNNING_ERROR_CODE = 0x420;
    if (StartService(service_handle, 0, nullptr))
    {
        return true;
    }

    auto last_error_code = GetLastError();
    if (last_error_code == SERVICE_ALREADY_RUNNING_ERROR_CODE)
    {
        logger::log("service already running\n");
        return true;
    }
    else
    {
        logger::log("unable to start service. error_code=(0x%lX)\n", last_error_code);
        return false;
    }
}

//
// stop the service
// sc stop myservice
//
bool service_utils::stop_service(SC_HANDLE service_handle)
{
    SC_HANDLE sc_manager_handle = open_sc_manager();

    CHECK_SC_MANAGER_HANDLE(sc_manager_handle, false);

    SERVICE_STATUS service_status;

    if (!ControlService(service_handle, SERVICE_CONTROL_STOP, &service_status))
    {
        logger::log("[!] failed to stop the service. (0x%lX)\n", GetLastError());
        CloseServiceHandle(sc_manager_handle);
        return false;
    }

    CloseServiceHandle(sc_manager_handle);

    return true;
}

#include "pch.h"
#include "MainPage.h"
#include "MainPage.g.cpp"
#include <winrt/Windows.Storage.h>
#include <winrt/Windows.Storage.Pickers.h>
#include <winrt/Windows.Storage.Provider.h>

using namespace winrt;
using namespace Windows::UI::Xaml;
using namespace Windows::Foundation;
using namespace Windows::Storage;
using namespace Windows::Storage::Pickers;
using namespace Windows::Storage::Provider;


namespace winrt::BlankApp6::implementation
{
    auto variable2 = 0;
    MainPage::MainPage()
    {
        InitializeComponent();
    }

    int32_t MainPage::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void MainPage::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }

    IAsyncAction MainPage::ClickHandler(IInspectable const&, RoutedEventArgs const&)
    {
        apartment_context ui_thread;
        FileSavePicker picker= FileSavePicker();
        StorageFile storage_picker=nullptr;
        //picker.ViewMode(PickerViewMode::Thumbnail);
        picker.SuggestedStartLocation(PickerLocationId::Desktop);
        //picker.FileTypeFilter().Append(L".txt");
        picker.FileTypeChoices().Insert(L"all_type", winrt::single_threaded_vector<winrt::hstring>({ L".txt" }));
        /*template <typename T, typename Allocator = std::allocator<T>>
          winrt::Windows::Foundation::Collections::IVector<T>
          single_threaded_vector(std::vector<T, Allocator> && values = {});*/

        picker.SuggestedFileName(L"helloworld.txt");

        storage_picker = co_await picker.PickSaveFileAsync();

        if (storage_picker != NULL)
        {
            co_await ui_thread;
            testbox1().Text(to_hstring(storage_picker.Name()));

            CachedFileManager::DeferUpdates(storage_picker);
            co_await FileIO::WriteTextAsync(storage_picker, L"hello123");
            co_await resume_background();
            FileUpdateStatus status1 = co_await CachedFileManager::CompleteUpdatesAsync(storage_picker);

            if (status1 == FileUpdateStatus::Complete)
            {   
                co_await ui_thread;
                testbox2().Text(L"complete");
            }
            else
            {
                co_await ui_thread;
               testbox2().Text(L"fail");
            }
        }
        if (storage_picker == NULL)
        {
            co_await ui_thread;
            testbox2().Text(L"fail");
        }
    }

    IAsyncAction MainPage::Openfilebtn_Click(IInspectable const& , RoutedEventArgs const& )
    {
        co_await resume_background();
    }
}



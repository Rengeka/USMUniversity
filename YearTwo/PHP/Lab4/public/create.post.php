<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Create post</title>
    <script src="https://cdn.tailwindcss.com"></script>
</head>
<body class="bg-gray-50 min-h-screen p-4 sm:p-8">
    <div class="max-w-3xl mx-auto bg-white rounded-xl shadow-sm transition-all duration-200 hover:shadow-md">
        <div class="p-6 md:p-8">
            <h2 class="text-3xl font-bold text-gray-800 mb-6">Create a new post</h2>
            
            <form action="../src/handlers/post.handlers/create.post.handler.php" method="POST" enctype="multipart/form-data" class="space-y-6">
                <div>
                    <label class="block text-sm font-medium text-gray-700 mb-2">Title</label>
                    <input type="text" name="title" 
                           class="w-full px-4 py-2.5 border border-gray-300 rounded-lg focus:ring-2 focus:ring-blue-200 focus:border-blue-500 placeholder-gray-400 transition-all"
                           placeholder="Enter the post title">
                </div>

                <div>
                    <label class="block text-sm font-medium text-gray-700 mb-2">Category</label>
                    <select name="category" 
                            class="w-full px-4 py-2.5 border border-gray-300 rounded-lg focus:ring-2 focus:ring-blue-200 focus:border-blue-500 appearance-none bg-select-arrow bg-no-repeat bg-right-2 bg-[length:24px]">
                        <option value="General">General</option>
                        <option value="News">News</option>
                        <option value="Entertainment">Entertainment</option>
                    </select>
                </div>

                <div>
                    <label class="block text-sm font-medium text-gray-700 mb-2">Text</label>
                    <textarea name="content" rows="5" 
                              class="w-full px-4 py-2.5 border border-gray-300 rounded-lg focus:ring-2 focus:ring-blue-200 focus:border-blue-500 placeholder-gray-400 resize-y min-h-[120px]"
                              placeholder="Write the post content..."></textarea>
                </div>

                <div>
                    <label class="block text-sm font-medium text-gray-700 mb-2">Tags</label>
                    <select name="tags[]" multiple 
                            class="w-full px-4 py-2.5 border border-gray-300 rounded-lg focus:ring-2 focus:ring-blue-200 focus:border-blue-500 h-32">
                        <option value="news" class="px-2 py-1 hover:bg-blue-50">News</option>
                        <option value="humor" class="px-2 py-1 hover:bg-blue-50">Humor</option>
                        <option value="technology" class="px-2 py-1 hover:bg-blue-50">Technology</option>
                    </select>
                    <p class="mt-1 text-sm text-gray-500">Use Ctrl/Cmd to select multiple tags</p>
                </div>

                <div>
                    <label class="block text-sm font-medium text-gray-700 mb-2">Image</label>
                    <div class="flex items-center justify-center w-full">
                        <label class="flex flex-col w-full cursor-pointer">
                            <div class="border-2 border-dashed border-gray-300 rounded-lg p-6 text-center hover:border-blue-400 transition-colors">
                                <svg class="mx-auto h-12 w-12 text-gray-400" stroke="currentColor" fill="none" viewBox="0 0 48 48">
                                    <path d="M28 8H12a4 4 0 00-4 4v20m32-12v8m0 0v8a4 4 0 01-4 4H12a4 4 0 01-4-4v-4m32-4l-3.172-3.172a4 4 0 00-5.656 0L28 28M8 32l9.172-9.172a4 4 0 015.656 0L28 28m0 0l4 4m4-24h8m-4-4v8m-12 4h.02" stroke-width="2" stroke-linecap="round" stroke-linejoin="round"/>
                                </svg>
                                <span class="block mt-2 text-sm text-gray-600">Drag and drop an image or click to upload</span>
                                <input type="file" name="image" class="hidden">
                            </div>
                        </label>
                    </div>
                </div>

                <button type="submit" 
                        class="w-full bg-gradient-to-br from-blue-500 to-blue-600 text-white px-6 py-3.5 rounded-lg font-medium hover:from-blue-600 hover:to-blue-700 transition-all shadow-sm hover:shadow-md">
                    Publish
                </button>
            </form>
        </div>
    </div>
</body>
</html>

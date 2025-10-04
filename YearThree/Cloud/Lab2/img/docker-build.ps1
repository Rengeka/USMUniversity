Write-Host "Removing old local image if exists..."
try {
    docker image rm -f rengeka/php-test-app:latest
} catch {
    Write-Host "Image does not exist, skipping..."
}

Write-Host "Building PHP app without cache..."
docker build --no-cache -t rengeka/php-test-app:latest -f dockerfile.php .

Write-Host "Pushing PHP app image to Docker Hub..."
docker login
docker push rengeka/php-test-app:latest

#mysql -h sql -u root -prootpassword mydatabase --skip-ssl < sql/seed.sql 
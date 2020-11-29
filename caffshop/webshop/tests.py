from datetime import date

from django.core.files.base import ContentFile
from django.core.files.uploadedfile import SimpleUploadedFile
from webshop.models import Comment, CAFF
from django.contrib.auth.models import User
from django.test import TestCase, Client
from django.urls import reverse

# Create your tests here.

class DetailBaseTest(TestCase):
    def setUp(self):
        self.content_1 = open("example/1.caff", "rb")
        self.uploaded_file_1 = SimpleUploadedFile("example/1.caff", self.content_1.read())
        self.user = User.objects.create_user(username='admin', password='admin')
        self.c = Client()  # above, from django.test import TestCase,Client
        self.c.login(username='admin', password='admin')
        self.c.post('/webshop/upload/', {'name': 'admin', 'content': self.uploaded_file_1})
        self.caff = CAFF.objects.get(name='admin')
        self.detail_url = '/webshop/' + str(self.caff.id) + '/'

class DetailTest(DetailBaseTest):
    def test_can_view_detail_page(self):
        response = self.c.get(self.detail_url)
        self.assertEqual(response.status_code, 200)

    def test_comment_success(self):
        

class CommentTestCase(TestCase):
    def setUp(self):
        Comment.objects.create(text="valami")
        Comment.objects.create(text="valami")
        Comment.objects.create(text="valami2")

    def test_multiple_get(self):
        flag = False
        try:
            valami = Comment.objects.get(text="valami")
        except:
            flag = True
        finally:
            self.assertEqual(flag, True)

    def test_single_get(self):
        valami2 = Comment.objects.get(text="valami2")
        self.assertEqual("valami2", valami2.text)
        self.assertEqual(date.today(), valami2.date)
        self.assertIsNone(valami2.user)
        self.assertIsNone(valami2.image)


class UserTestCase(TestCase):
    def test_create_user(self):
        user = User.objects.create_user(username='john',
                                        email='jlennon@beatles.com',
                                        password='glass onion')
        self.assertEqual(user.username, "john")
        self.assertEqual(user.email, "jlennon@beatles.com")
        self.assertNotEqual(user.password, 'glass onion')
    def test_create_same_usernames(self):
        user = User.objects.create_user(username='john',
                                        email='jlennon@beatles.com',
                                        password='glass onion')
        flag = False
        try:
            user2 = User.objects.create_user(username='john',
                                             email='jlennon@beatles.com',
                                             password='glass onion')
        except:
            flag = True
        finally:
            self.assertEqual(flag, True)

class BaseTest(TestCase):
    def setUp(self):
        self.user = User.objects.create_user(username='john',
                                        email='jlennon@beatles.com',
                                        password='glass onion')
        self.caff = CAFF.objects.create(user=self.user)

    def test_create_caff_user(self):
        self.assertEqual(self.caff.user, self.user)

class UploadCAFFFormTestCase(TestCase):

    def setUp(self):
        self.content_1 = open("example/1.caff", "rb")
        self.content_2 = open("example/2.caff", "rb")
        self.content_3 = open("example/3.caff", "rb")
        self.uploaded_file_1 = SimpleUploadedFile("example/2.caff", self.content_1.read())
        self.uploaded_file_2 = SimpleUploadedFile("example/1.caff", self.content_2.read())
        self.uploaded_file_3 = SimpleUploadedFile("example/3.caff", self.content_3.read())
        self.user = User.objects.create_user(username='admin',
                                             password='admin')
        self.c = Client()  # above, from django.test import TestCase,Client
        self.c.login(username='admin', password='admin')

    def test_upload_caff_1(self):
        response = self.c.post('/webshop/upload/', {'name': 'admin', 'content': self.uploaded_file_1})
        self.assertEqual(response.status_code, 302)

    def test_upload_caff_2(self):
        response = self.c.post('/webshop/upload/', {'name': 'admin', 'content': self.uploaded_file_2})
        self.assertEqual(response.status_code, 302)

    def test_upload_caff_3(self):
        response = self.c.post('/webshop/upload/', {'name': 'admin', 'content': self.uploaded_file_3})
        self.assertEqual(response.status_code, 200)
    
class LoginViewTestCase(TestCase):

    def setUp(self):
        self.user = User.objects.create_user(username='admin',
                                        password='admin')
        self.c = Client()  # above, from django.test import TestCase,Client


    def test_login_valid(self):
        response = self.c.post('/login/', {'username': 'admin', 'password': 'admin'})
        self.assertEqual(response.status_code, 302)

    def test_login_not_valid(self):
        response = self.c.post('/login/', {'username': 'admin', 'password': 'asd'})
        self.assertEqual(response.status_code, 200)
